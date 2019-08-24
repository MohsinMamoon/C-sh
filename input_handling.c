#include "decl.h"
#include "defs.h"

int parse_command(char *input_cmd, int index)
{
    char *ptr = input_cmd, *save_ptr, delim[] = " \t";
    int j = 0;
    if(ptr == NULL) return index - 1;
    command[index].command = strtok_r(ptr, delim, &save_ptr);
    for (j = 0, ptr = (char*)NULL;; j++, ptr = (char *)NULL)
    {
        command[index].arguments[j] = strtok_r(ptr, delim, &save_ptr);
        if (command[index].arguments[j] == (char *)NULL)
            break;
        if(!strncmp(command[index].arguments[j],"&", 1) || !strncmp(command[index].command, "&", 1)){ 
            delim[0] = delim[1] = '\0';
            
            if(!strncmp(command[index].command, "&", 1)) {
                command[index].command = NULL;
                index = parse_command(strtok_r(ptr, delim, &save_ptr), index);
            }

            else {
                command[index].arguments[j] = NULL;
                bckgrnd[index] = 1;
                index = parse_command(strtok_r(ptr, delim, &save_ptr), index+1);
            }
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

int parse_dir(char ** inp, char** dir, char * cmd, char * final) {
    int in_ind = 0, dir_ind = 0, mode = 0;
    
    if(inp[in_ind] == NULL) {
        inp[in_ind] = (!strcmp(cmd, "cd")) ? "~" : ".";
    }

    while(inp[in_ind] != NULL) {
        if(inp[in_ind][0] == '-' && !strcmp(cmd, "ls")) {
            switch (mode)
            {
            case 0:
                if(!strcmp(&inp[in_ind][1], "la") || !strcmp(&inp[in_ind][1], "al")) mode = 3;
                else if(!strcmp(&inp[in_ind][1], "a")) mode = 2;
                else if(!strcmp(&inp[in_ind][1], "l")) mode = 1;
                break;
            case 1:
                if(!strcmp(&inp[in_ind][1], "la") || !strcmp(&inp[in_ind][1], "al")) mode = 3;
                else if(!strcmp(&inp[in_ind][1], "a")) mode = 3;
                break;
            case 2:
                if(!strcmp(&inp[in_ind][1], "la") || !strcmp(&inp[in_ind][1], "al")) mode = 3;
                else if(!strcmp(&inp[in_ind][1], "l")) mode = 3;
                break;
            default:
                break;
            }
            in_ind++;
            continue;
        }
        if(inp[in_ind][0] == '"' | inp[in_ind][0] == '\'') {
            char temp[50000];
            combine(inp, inp[in_ind][0], temp);
            inp[in_ind] = temp;
        }
        if(!strcmp(cmd, "ls")) {
            for(int i_st = strlen(final), j_st = 0; j_st<strlen(inp[in_ind]); i_st++, j_st++) {
                final[i_st] = inp[in_ind][j_st];
            }
            final[strlen(final)] = '-';
            final[strlen(final)] = '\0';
        } 
        if (inp[in_ind][0] == '.' && strlen(inp[in_ind]) == 1) {
            dir[dir_ind] = cur_dir;
        }
        else if(inp[in_ind][0] == '~') {
            char temp[50000];
            for(int i=0;i<strlen(home_dir); i++) temp[i] = home_dir[i];
            temp[strlen(home_dir)] = '\0';
            strcat(temp, &inp[in_ind][1]);
            dir[dir_ind] = temp;
        }
        else {
            char *p = (char *) malloc ((strlen(cur_dir) + strlen(home_dir) + strlen(inp[in_ind])) * sizeof(char));
            realpath(inp[in_ind], p);
            dir[dir_ind] = p;
        }
        in_ind++;
        dir_ind++;
        if (!strcmp(cmd,"cd")) break; 
    }
    return mode;
}
