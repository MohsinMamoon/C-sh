#include "defs.h"
#include "decl.h"

void sys(cmd command, _Bool back) {
    char* args[1000];
    args[0] = command.command;
    for(int i=0;; i++) {
        if((args[i+1] = command.arguments[i]) == NULL) break;
    }

    int pid = fork();

    if(pid != 0) {
        // Parent
        if(command.pipe_out != -1) close(pipe_fd[command.pipe_out]);
        
        if(!back) waitpid(pid, NULL, WUNTRACED);
    }
    else if(pid == 0) {
        // Child
        if(command.pipe_in != -1 || command.pipe_out != -1) {
            if(command.pipe_in != -1) dup2(pipe_fd[command.pipe_in], 0);
            if(command.pipe_out != -1) dup2(pipe_fd[command.pipe_out], 1);
            for(int i=0; i<2*pipe_no; i++) {
                close(pipe_fd[i]);
            }
        }
        
                if(back) setpgid(0,0);
        execvp(args[0], args);
        fprintf(stderr, "Execution error: Command not found!\n");
        exit(0);
    }
    else {
        fprintf(stderr, "Forking error\n\n");
        exit(1);
    }
    return;

    
}
