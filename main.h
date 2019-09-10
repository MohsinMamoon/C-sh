#include <stdio.h>

typedef struct jb {
    char job_name[1000];
    int job_id;
    int job_pid;
    _Bool in_back;
}job;

job background[1000];
int no_of_jobs;


typedef struct commands {
    char *command;
    char *arguments[1000];
    char *in, *out;
    _Bool in_redir, out_redir, append;
    int pipe_in, pipe_out;
} cmd;

cmd *command;
_Bool *bckgrnd;
char cur_dir[10000], home_dir[10000], hist_dir[10000];
static int cmd_num, his_num = 0;
FILE *his_fd;
char his[20000];
int orig_stdin, orig_stdout;
int *pipe_fd, pipe_no, i_pip;