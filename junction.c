#include "decl.h"
#include "defs.h"

void execute(int cmd) {
    if(!strcmp(command[cmd].command, "clear")) {
        printf("\e[1;1H\e[2J");
    }
    else if(!strcmp(command[cmd].command, "quit") | !strcmp(command[cmd].command, "exit")) {
        exit(0);
    }
    else if(!strcmp(command[cmd].command, "ls")) {
    //    ls(command[cmd]);
    }
    else if(!strcmp(command[cmd].command, "cd")) {
       cd(command[cmd]);
    } 
    else if(!strcmp(command[cmd].command, "echo")) {
      //  echo(command[cmd], bckgrnd[cmd]);
        printf("This is ls");
    } 
    else if(!strcmp(command[cmd].command, "pwd")) {
        getcwd(cur_dir, sizeof(cur_dir));
        printf("Present Working Directory: %s\n", cur_dir);
    } 
    else if(!strcmp(command[cmd].command, "pinfo")) {
      //  pinfo(command[cmd], bckgrnd[cmd]);
        printf("This is ls");

    } 
    else if(!strcmp(command[cmd].command, "nightswatch")) {
       // nightswatch(command[cmd], bckgrnd[cmd]);
        printf("This is ls");
    } 
    else if(!strcmp(command[cmd].command, "history")) {
       // history(command[cmd], bckgrnd[cmd]);
        printf("This is ls");
    } 
    else {
      //  sys(command[cmd], bckgrnd[cmd]);
      if(command[cmd].command[0] >= 'a' && command[cmd].command[0] <='z') printf("Yet to decide what to do with you!\n");
      else printf("Not a valid command dude!\n");
    }
    return;
}