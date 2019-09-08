#include "decl.h"
#include "defs.h"

void echo(cmd command) {
    int pid = fork();

    if(pid) {
        if(command.pipe_out != -1) close(pipe_fd[command.pipe_out]);
        wait(NULL);
    }    
    else if(pid == 0) {
        if(command.pipe_in != -1 || command.pipe_out != -1) {
            if(command.pipe_in != -1) dup2(pipe_fd[command.pipe_in], 0);
            if(command.pipe_out != -1) dup2(pipe_fd[command.pipe_out], 1);
            for(int i=0; i<2*pipe_no; i++) {
                close(pipe_fd[i]);
            }
        }

        int i = 0;
        while (command.arguments[i] != NULL) {
            printf("%s ", command.arguments[i]);
            i++;
        }
        printf("\n\n");
        exit(0);
    }
    else {
        fprintf(stderr, "Forking error!\n");
        return;
    }
}