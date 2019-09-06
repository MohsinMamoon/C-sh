#include <stdio.h>

typedef struct commands {
    char *command;
    char *arguments[1000];
    char *in, *out;
    _Bool in_redir, out_redir, append;
} cmd;

cmd *command;
_Bool *bckgrnd;
char cur_dir[10000], home_dir[10000], hist_dir[10000];
static int cmd_num, his_num = 0;
FILE *his_fd;
char his[20000];
int orig_stdin, orig_stdout;