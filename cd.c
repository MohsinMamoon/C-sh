#include "decl.h"
#include "defs.h"

void cd(cmd command){
    char **dir;
    dir = (char **) malloc (sizeof(char*));
    memset(dir, 0, sizeof(dir));
    parse_dir(command.arguments, dir, "cd", (char *)NULL);
    if(chdir(dir[0])){
        fprintf(stderr, "Error: File or Directory doesnot exist!\n pwd: %s\n", cur_dir);
    }
    getcwd(cur_dir, sizeof(cur_dir));
    free(dir);
    return;
}
