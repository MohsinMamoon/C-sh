#include "decl.h"
#include "defs.h"
#include "main.h"

int parse_command(char *input_cmd, int index)
{
    char *ptr = input_cmd, *save_ptr, delim = ' ';
    int j = 0;
    command[index].command = strtok_r(ptr, &delim, &save_ptr);
    for (j = 0, ptr = (char*)NULL;; j++, ptr = (char *)NULL)
    {
        command[index].arguments[j] = strtok_r(ptr, &delim, &save_ptr);
        if (command[index].arguments[j] == (char *)NULL)
            break;
        if(!strncmp(command[index].arguments[j],"&", 1)){ 
            command[index].arguments[j] = NULL;
            bckgrnd[index] = 1;
            delim = (char) NULL;
            index = parse_command(strtok_r(ptr, &delim, &save_ptr), index+1);
            break;
        }
    }
    return index;
}

int parse_input(char *input)
{
    char *ptr1 = input, *ptr2, *save_ptr, delim = ';';
    int i = 0;
    for (;; i++, ptr1 = NULL)
    {
        ptr2 = strtok_r(ptr1, &delim, &save_ptr);
        if (ptr2 == NULL)
            break;
        i = parse_command(ptr2, i);
    }
    return i;
}

void parse_dir(char * inp, char*** dir) {
    int index = 0;
    while(*dir[index] != NULL) index++;
    if (inp[0] == '.' && strlen(inp) == 1) {
        *dir[index] = cur_dir;
    }
    else if(inp[0] == '~') {
        *dir[index] = home_dir;
    }
    else {
        char *p = (char *) malloc ((strlen(cur_dir) + strlen(home_dir) + strlen(inp)) * sizeof(char));
        realpath(inp, p);
        *dir[index] = p;
    }
    return;
}
