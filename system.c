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
        out_close(command);
        if(!back) {
            waitpid(pid, NULL, WUNTRACED);
        }
        if(back || !kill(pid, 0)) {
            add_job(pid, command);
        }
    }
    else if(pid == 0) {
        // Child
        piping_begin(command);
        
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
