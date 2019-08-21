#include "decl.h"
#include "defs.h"

int parse_command(char *input_cmd, int index)
{
    char *ptr = input_cmd, *save_ptr, delim[] = " \t";
    int j = 0;
    command[index].command = strtok_r(ptr, delim, &save_ptr);
    for (j = 0, ptr = (char*)NULL;; j++, ptr = (char *)NULL)
    {
        command[index].arguments[j] = strtok_r(ptr, delim, &save_ptr);
        if (command[index].arguments[j] == (char *)NULL)
            break;
        if(!strncmp(command[index].arguments[j],"&", 1)){ 
            command[index].arguments[j] = NULL;
            bckgrnd[index] = 1;
            delim[0] = delim[1] = '\0';
            index = parse_command(strtok_r(ptr, delim, &save_ptr), index+1);
            break;
        }
    }
    return index;
}

int parse_input(char *input)
{
    char *ptr1 = input, *ptr2, *save_ptr, delim[] = ";";
    int i = 0;
    for (;; i++, ptr1 = NULL)
    {
        ptr2 = strtok_r(ptr1, delim, &save_ptr);
        if (ptr2 == NULL)
            break;
        i = parse_command(ptr2, i);
    }
    return i;
}

void parse_dir(char ** inp, char*** dir, char * cmd) {
    int index = 0;
    while(*dir[index] != NULL) index++;
    
    if(inp[index] == NULL) {
        inp[index] = "~";
    }

    while(inp[index] != NULL) {
        
        if(inp[index][0] == '"' | inp[index][0] == '\'') {
            char temp[50000];
            combine(inp, inp[index][0], temp);
            inp[index] = temp;
        }

        if (inp[index][0] == '.' && strlen(inp[index]) == 1) {
            *dir[index] = cur_dir;
        }
        else if(inp[index][0] == '~') {
            char temp[50000];
            for(int i=0;i<strlen(home_dir); i++) temp[i] = home_dir[i];
            temp[strlen(home_dir)] = '\0';
            strcat(temp, &inp[index][1]);
            *dir[index] = temp;
        }
        else {
            char *p = (char *) malloc ((strlen(cur_dir) + strlen(home_dir) + strlen(inp[index])) * sizeof(char));
            realpath(inp[index], p);
            *dir[index] = p;
        }
        index++;
        if (!strcmp(cmd,"cd")) break; 
    }
    return;
}

void combine(char **array, char sign, char* new) {
    int i=0;
    for(i=0; array[i] != NULL; i++) {
        if(array[i][strlen(array[i])-1] == sign) break;
    }
    int l=0;
    for(int j=0; j<=i; j++) {
        for(int k=0; array[j][k] != '\0';k++) {
            if(array[j][k] != sign) new[l++] = array[j][k]; 
        }
        if(i != j) new[l++] = ' ';
    }
    new[l] = '\0';
    return;
}