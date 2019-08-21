#include "decl.h"
#include "defs.h"
// #include "main.h"

void execute(int cmd) {
    if(!strcmp(command[cmd].command, "clear")) {
        printf("\e[1;1H\e[2J");
    }
    else if(!strcmp(command[cmd].command, "quit") | !strcmp(command[cmd].command, "exit")) {
        exit(0);
    }
    else if(!strcmp(command[cmd].command, "ls")) {
       // ls(command[cmd], bckgrnd[cmd]);
        printf("This is ls");
        char **dir;
        dir = (char **) malloc (sizeof(char*));
        dir[0] = NULL;
        parse_dir(command[cmd].arguments[0], &dir);
        printf("The path is: %s\n", dir[0]);
    }
    else if(!strcmp(command[cmd].command, "cd")) {
       cd(command[cmd]);
    } 
    else if(!strcmp(command[cmd].command, "echo")) {
      //  echo(command[cmd], bckgrnd[cmd]);
        printf("This is ls");
    } 
    else if(!strcmp(command[cmd].command, "pwd")) {
       // pwd(command[cmd], bckgrnd[cmd]);
        printf("This is ls");
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
        printf("This is ls");
    }
    return;
}