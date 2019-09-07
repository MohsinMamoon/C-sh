#include "defs.h"
#include "decl.h"
void back_end(int sig) {
    int p_id, ext_stat;
    while((p_id = waitpid(-1, &ext_stat, WUNTRACED | WNOHANG)) >= 1) {
        if(WIFEXITED(ext_stat)) {
            fprintf(stderr, "Process with pid %d terminated normally with status %d!\n\n", p_id, WEXITSTATUS(ext_stat));
        }
        else if(WIFSIGNALED(ext_stat)) {
            fprintf(stderr, "Process with pid %d terminated by signal %d!\n\n", p_id, WTERMSIG(ext_stat));
        }
    }
}
void sys(cmd command, _Bool back) {
    char* args[1000];
    args[0] = command.command;
    for(int i=0;; i++) {
        if((args[i+1] = command.arguments[i]) == NULL) break;
    }

    int pid = fork();

    if(pid != 0) {
        // Parent
        if(!back) wait(NULL);
    }
    else if(pid == 0) {
        // Child
        // sleep(2);
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
