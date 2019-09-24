#include "defs.h"
#include "decl.h"

void up_exec(cmd comm) {
    
    int up_arr = 0, start=0, size=0;
    char s[5];
    
    for(int i=2; i<strlen(comm.command); i += 3){
        if(comm.command[i] == 'A') up_arr++;
    }
    
    for(int i=strlen(his)-2, j=0; i>=0; i--) {
        if(his[i] == '+') j++;
        if(j == up_arr) {
        start = i+1;
        break;
        }
    }
    
    for(int i=start; i<strlen(his); i++) {
        if(his[i] == '+') break;
        size++;
    }
    
    char *input = (char*) malloc (sizeof(char) * size+1);
    
    for(int i=0; i<size; i++) {
        input[i] = his[start+i];
    }
    input[size] = '\0';
    
    display_shell();
    printf("%s\n", input);
    
    if(input[0] != '\033' && input[0] != '\f'&& input[0] != '\0') add_to_hist(input, size);
    
    // Reset variables and add to history
    pipe_no =  0;
    i_pip = 1;

    // Setting up commands
    free(bckgrnd);
    free(command);
    command = (cmd *)malloc(sizeof(cmd) * size);
    memset(command->arguments, 0, sizeof(command->arguments));        
    bckgrnd = (_Bool *) malloc (sizeof(_Bool) * size);
    memset(bckgrnd,0,size * sizeof(_Bool));
    cmd_num = parse_input(input);

    // Setting up pipes
    pipes_setup();

    // Executing commands
    for(int i=0; i<cmd_num; i++){ 
        if(command[i].command != NULL && command[i].command[0] != ' ') execute(i);
    }
    
    free(input);        
    return;
}