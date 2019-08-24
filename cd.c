#include "decl.h"
#include "defs.h"

void cd(cmd command){
    char **dir;
    dir = (char **) malloc (sizeof(char*));
    memset(dir, 0, sizeof(dir));
    parse_dir(command.arguments, dir, "cd", (char *)NULL);
    if(chdir(dir[0])){
        perror("Error");
        write(2, cur_dir, strlen(cur_dir));
        write(2, "\n", 1);
    }
    getcwd(cur_dir, sizeof(cur_dir));
    free(dir);
    return;
}
