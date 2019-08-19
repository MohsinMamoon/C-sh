#include "decl.h"

int parse_input(char *input, _Bool *background)
{
    char *ptr1 = input, *ptr2, *save_ptr, delim = ';';
    int i = 0;
    for (;; i++, ptr1 = NULL)
    {
        ptr2 = strtok_r(ptr1, &delim, &save_ptr);
        if (ptr2 == NULL)
            break;
        parse_command(ptr2, background, i);
    }
    return i;
}

void parse_command(char *input_cmd, _Bool *background, int index)
{
    char *ptr = input_cmd, *save_ptr, delim = ' ';
    int j = 0;
    command[index].command = strtok_r(ptr, &delim, &save_ptr);
    for (j = 0, ptr = (char*)NULL;; j++, ptr = (char *)NULL)
    {
        command[index].arguments[j] = strtok_r(ptr, &delim, &save_ptr);
        if (command[index].arguments[j] == (char *)NULL)
            break;
    }
}