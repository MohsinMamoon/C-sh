#include "main.h"

void gethd(char *home, int pid);
void display_shell();
int parse_input(char *input);
void execute(int cmd);
void cd(cmd command);
void ls(cmd command);
void pinfo(cmd command);
void back_end(int sig);
void nightswatch(cmd command, _Bool back);
void history(cmd command);
void init_hist();
void add_to_hist(char *input, int size);
void sys(cmd command, _Bool back);
int parse_dir(char ** inp, char** dir, char * cmd, char* final);
void interrupt(int time);
void dirty(int time);
