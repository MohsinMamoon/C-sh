typedef struct commands {
    char *command;
    char *arguments[1000];
} cmd;

cmd *command;
_Bool *bckgrnd;
char *cur_dir, *home_dir;
int cmd_num;
