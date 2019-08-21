#include "decl.h"
// #include "main.h"
#include "defs.h"

void cd(cmd command){
    char **dir, *temp;
    if(command.arguments[0] == NULL) {
        command.arguments[0] = "~";
    }
    else if(command.arguments[0][0] == '"' | command.arguments[0][0] == '\'') {
        char temp[50000];
        combine(command.arguments, command.arguments[0][0], temp);
        command.arguments[0] = temp;
    }
    dir = (char **) malloc (sizeof(char*));
    memset(dir, 0, sizeof(dir));
    parse_dir(command.arguments[0], &dir);
    if(chdir(dir[0])){
        perror("chdir");
    }
    return;
}
