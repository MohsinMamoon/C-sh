typedef struct commands {
    char *command;
    char *arguments[1000];
} cmd;

cmd *command;
_Bool *bckgrnd;
char cur_dir[10000], home_dir[10000];
int cmd_num;
