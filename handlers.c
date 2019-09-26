#include "decl.h"
#include "defs.h"

void back_end(int sig) {
    int p_id, ext_stat;
    for(int i=0; i<no_of_jobs; i++) {
        if(background[i%1000].in_back && (p_id = waitpid(background[i].job_pid, &ext_stat, WUNTRACED | WNOHANG)) > 0) {
            if(WIFEXITED(ext_stat)) {
                if(strncmp(background[i].job_name, "cronjob", 7)){
                    fprintf(stderr, "%s with pid %d terminated ", background[i].job_name, background[i].job_pid);
                    fprintf(stderr, "normally with status %d!\n", WEXITSTATUS(ext_stat));
                }
                rem_job(background[i].job_id);
            }
            else if(WIFSIGNALED(ext_stat)) {
                fprintf(stderr, "%s with pid %d terminated ", background[i].job_name, background[i].job_pid);
                fprintf(stderr, "by signal %d!\n",WTERMSIG(ext_stat));
                rem_job(background[i].job_id);
            }
        }
    }
}

void back_send(int sig) {
    setpgid(0, 0);
    kill(getpid(), SIGSTOP);
}

void EOF_IGN() {
    struct termios old, new;
    tcgetattr(0,&old);
    new = old;
    new.c_cc[VEOF] = 3;
    tcsetattr(0,TCSANOW,&new);
}

void signal_setup() {
    signal(SIGCHLD, back_end);
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    EOF_IGN();
}