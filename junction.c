#include "decl.h"
#include "defs.h"

void execute(int cmd) {
    if(!strcmp(command[cmd].command, "clear")) {
        printf("\e[1;1H\e[2J");
    }
    else if(!strcmp(command[cmd].command, "quit") || !strcmp(command[cmd].command, "exit") || (strlen(command[cmd].command) == 1 && command[cmd].command[0] == 'q')) {
        exit(0);
    }
    else if(!strcmp(command[cmd].command, "ls")) {
       ls(command[cmd]);
    }
    else if(!strcmp(command[cmd].command, "cd")) {
       cd(command[cmd]);
    } 
    else if(!strcmp(command[cmd].command, "echo")) {
      int i = 0;
      while(command[cmd].arguments[i] != NULL) {
        printf("%s ", command[cmd].arguments[i]);
        i++;
      }
      printf("\n\n");
    } 
    else if(!strcmp(command[cmd].command, "pwd")) {
        getcwd(cur_dir, sizeof(cur_dir));
        printf("Present Working Directory: %s\n\n", cur_dir);
    } 
    else if(!strcmp(command[cmd].command, "pinfo")) {
       pinfo(command[cmd]);
    } 
    else if(!strcmp(command[cmd].command, "nightswatch")) {
      nightswatch(command[cmd], bckgrnd[cmd]);
    } 
    else if(!strcmp(command[cmd].command, "history")) {
       history(command[cmd]);
    } 
    else {
       sys(command[cmd], bckgrnd[cmd]);
    }
}
