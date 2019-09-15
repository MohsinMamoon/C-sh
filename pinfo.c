#include "decl.h"
#include "defs.h"

void pinfo(cmd command) {
    int pid = fork();
    if(pid) {
        out_close(command);
        wait(NULL);
    }
    else if(pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, back_send);
      
        piping_begin(command);
        
        char home[1000], s_pid[20], memory[100], stat_path[1000], stat_in[1000], exec_path[]="/proc/", temp2[] = "/stat", temp3[] = "/exe", p_status;
        memset(stat_path, 0, sizeof(stat_path));
        size_t len = 0;
        if(command.arguments[0] == NULL) {
            int pid = getppid();
            sprintf(s_pid, "%d", pid);
        }
        else {
            for(int i=0; ;i++) {
                s_pid[i] = command.arguments[0][i];
                if(s_pid[i] == '\0') break;
            }
        }
        printf("pid: %s\n", s_pid);
        strncat(exec_path,s_pid,strlen(s_pid));
        strncpy(stat_path, exec_path, strlen(exec_path));
        strcat(exec_path, temp3);
        strcat(stat_path, temp2);
        realpath(exec_path, home);

        FILE  *file = fopen(stat_path, "r");
        if(file == NULL) {
            fprintf(stderr, "Invalid Process ID! \n");
            return;
        }
        int spaces = 0;
        while(spaces < 23) {
            fscanf(file, "%s", stat_in);
            if(spaces == 2) p_status = stat_in[0];
            if(spaces == 22) for(int i=0; i<strlen(stat_in); i++) memory[i] = stat_in[i];
            spaces ++;
        }
        printf("Process Status: %c\nMemory: %s\nExecutable Path: %s\n", p_status, memory, home);
        fclose(file);
        exit(0);
    }
    else {
        fprintf(stderr, "Fork Error!\n");
        return;
    }
}
