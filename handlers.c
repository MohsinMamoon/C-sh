#include "decl.h"
#include "defs.h"

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

void back_send(int sig) {
    setpgid(0, 0);
    kill(getpid(), SIGSTOP);
}

void signal_setup() {
    signal(SIGCHLD, back_end);
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}