#include "main.h"

void gethd(char *home, int pid);
void display_shell();
int parse_input(char *input);
void execute(int cmd);
void cd(cmd command);
//void ls(cmd command, _Bool back);
//void echo(cmd command, _Bool back);
//void pwd(cmd command, _Bool back);
//void pinfo(cmd command, _Bool back);
//void nightswatch(cmd command, _Bool back);
//void history(cmd command, _Bool back);
//void sys(cmd command, _Bool back);
void parse_dir(char * inp, char*** dir);
void combine(char **array, char sign, char* final);