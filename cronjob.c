#include "defs.h"
#include "decl.h"

void cronjob(cmd comd, _Bool back) {
    int period = 0, total = 0, cmd_ind;
    for(int i=0; comd.arguments[i] != NULL; i++) {
        if(!strcmp(comd.arguments[i], "-t")) {
            if(comd.arguments[i+1] != NULL) {
                sscanf(comd.arguments[i+1], "%d", &period);
            }
            else {
                fprintf(stderr, "Invalid period!\n");
                return;
            }
        }
        else if(!strcmp(comd.arguments[i], "-p")) {
            if(comd.arguments[i+1] != NULL) {
                sscanf(comd.arguments[i+1], "%d", &total);
            }
            else {
                fprintf(stderr, "Invalid total time!\n");
                return;
            }
        }
        else if(!strcmp(comd.arguments[i], "-c")) {
            if(comd.arguments[i+1] != NULL) cmd_ind = i+1;
            else {
                fprintf(stderr, "Invalid comd!\n");
                return;
            }
        }

    } 
    if(cmd_ind < 0 || total < 0 || period < 0) {
        fprintf(stderr, "Invalid syntax!\n");
        return;
    }
    command[cmd_num+1].command = comd.arguments[cmd_ind];
    for(int i=cmd_ind+1, j=0; ;i++, j++) {
        if(!strcmp(comd.arguments[i], "-t") || !strcmp(comd.arguments[i], "-p")) {
            command[cmd_num+1].arguments[j] = NULL;
            break;
        }
        else {
            command[cmd_num+1].arguments[j] = comd.arguments[i];
        }
    }
    int pid = fork();
    
    if(pid != 0) {    
        if(comd.pipe_out != -1) close(pipe_fd[comd.pipe_out]);

        add_job(pid, comd);
    }
    else if(pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, back_send);

        if(comd.pipe_in != -1 || comd.pipe_out != -1) {
            if(comd.pipe_in != -1) dup2(pipe_fd[comd.pipe_in], 0);
            if(comd.pipe_out != -1) dup2(pipe_fd[comd.pipe_out], 1);
            for(int i=0; i<2*pipe_no; i++) {
                close(pipe_fd[i]);
            }
        }
        
        setpgid(0,0);
        
        for(int i=0; i<total; i += period) {
            sleep(period);
            execute(cmd_num+1);
            printf("\n");
        }
        exit(0);
    }
    else {
        fprintf(stderr, "Forking error!\n");
        return;
    }
}