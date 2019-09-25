#include "defs.h"
#include "decl.h"

void add_job(int pid, cmd cmmd){
    char command[500];
    int i=0;
    for(i=0; i < strlen(cmmd.command); i++) {
        command[i] = cmmd.command[i];
    }
    command[i++] = ' ';
    for(int j=0; ;j++) {
        if(cmmd.arguments[j] == NULL) break;
        for(int k=0; k<strlen(cmmd.arguments[j]); k++) {
            command[i++] = cmmd.arguments[j][k];
        }
        command[i++ ] = ' ';
    }
    command[i] = '\0';
   
    job new;
    strcpy(new.job_name, command);
    new.job_id = ++no_of_jobs;
    new.job_pid = pid;
    new.in_back = 1;

    background[(no_of_jobs - 1) % 1000] = new;
    if(strncmp(command, "cronjob", 7)) printf("[%d] %s (%d) sent to background\n", no_of_jobs, command, pid);
    return;
}

void rem_job(int job_id){
    background[(job_id - 1) % 1000].in_back = 0;
}

void jobs(cmd command){
    int pid = fork();

    if (pid) {
        out_close(command);
        wait(NULL);
    }
    else if(pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, back_send);
        
        piping_begin(command);
        
        int printed = 0;
        for (int i = 0; i < no_of_jobs; i++){
            if (background[i % 1000].in_back){
            
                int j_id = background[i % 1000].job_id, pid = background[i % 1000].job_pid;
                char *name = background[i % 1000].job_name, st[40];
                char path[] = "/proc/", temp[] = "/stat", s_pid[20], stat_in[1000];
                sprintf(s_pid, "%d", pid);
                strcat(path, strcat(s_pid, temp));

                FILE *file = fopen(path, "r");
                if (file == NULL){
                    fprintf(stderr, "Open Error!\n");
                    return;
                }
                int spaces = 0;
                while (spaces < 3){
                    fscanf(file, "%s", stat_in);
                    spaces++;
                }
                switch (stat_in[0]) {
                case 'R':
                    strncpy(st, "Running", 7);
                    break;
                case 'S':
                    strncpy(st, "Sleeping", 8);
                    break;
                case 'D':
                    strncpy(st, "Waiting", 7);
                    break;
                case 'Z':
                    strncpy(st, "Zombie", 6);
                    break;
                case 'T':
                    strncpy(st, "Stopped", 7);
                    break;
                case 't':
                    strncpy(st, "Tracing stop", 12);
                    break;
                case 'X':
                case 'x':
                    strncpy(st, "Dead", 4);
                    break;
                case 'K':
                    strncpy(st, "Wakekill", 8);
                    break;
                case 'W':
                    strncpy(st, "Waking", 6);
                    break;
                case 'P':
                    strncpy(st, "Parked", 6);
                    break;
                }

                printf("[%d] %s %s %d\n", j_id, st, name, pid);
                printed++;
            }
        }
        if (printed == 0) fprintf(stderr, "No background jobs!\n");
        exit(0);
    }
    else {
        fprintf(stderr, "Fork Error!");
        return;
    }
}

void kjob(cmd command) {
    if(command.arguments[0] == NULL || command.arguments[1] == NULL) {
        fprintf(stderr, "Invalid syntax!\n");
        return;
    }
    else {
        int signal, job_id;
        sscanf(command.arguments[0], "%d", &job_id);
        sscanf(command.arguments[1], "%d", &signal);

        job cur = background[(job_id-1) % 1000];
        if(!cur.in_back || cur.job_name == NULL) {
            fprintf(stderr, "Job ID %d does not exist!\n", job_id);
            return;
        }
        else if(signal < 0 || signal > 31 || signal == 5 || signal == 7 || signal == 28 || signal == 29) {
            fprintf(stderr, "Invalid signal number!\n");
            return;
        }
        else {
            kill(cur.job_pid, signal);
        }
        return;
    }
}

void fg(cmd command) {
    int job_id;
    if(command.arguments[0] == NULL) {
        job_id = no_of_jobs;
    }
    else {
        sscanf(command.arguments[0], "%d", &job_id);
    }
    
    job cur = background[(job_id-1) % 1000];
    if(!cur.in_back || cur.job_name == NULL) {
        fprintf(stderr,"Job id %d does not exist!\n", job_id);
        return;
    }
    else {
        int pid = cur.job_pid;
        signal(SIGTTOU, SIG_IGN);
        if(getpgid(pid) != tcgetpgrp(0)) tcsetpgrp(0, pid);
        kill(pid, SIGCONT);
        waitpid(pid, NULL, WUNTRACED);
        if(kill(pid, 0) != 0)rem_job(job_id);
        tcsetpgrp(0, getpid());
        signal(SIGTTOU, SIG_DFL);
    }
}

void bg(cmd command) {
    int job_id;
    if(command.arguments[0] == NULL) {
        job_id = no_of_jobs;
    }
    else {
        sscanf(command.arguments[0], "%d", &job_id);
    }
    
    job cur = background[(job_id-1) % 1000];
    if(!cur.in_back || cur.job_name == NULL) {
        fprintf(stderr,"Job id %d does not exist!\n", job_id);
        return;
    }
    else {
        int pid = cur.job_pid;
        kill(pid, SIGCONT);
    }
}

void overkill() {
    for(int i=0; i<no_of_jobs; i++) {
        if(background[i%1000].in_back) kill(background[i%1000].job_pid, 9);
    }
    return;
}