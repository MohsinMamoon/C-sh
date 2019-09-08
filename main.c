#include "decl.h"
#include "defs.h"

int main()
{   
    //Inititalization
    char *input_buffer;
    size_t len;
    printf("\e[1;1H\e[2J");         
    gethd(home_dir, getpid());
    init_hist();

    while (1)
    {
        // Setting up signal handlers
        signal_setup();

        // Shell Prompt
        display_shell();

        // Resetting variables
        input_buffer = NULL;
        len = pipe_no =  0;
        i_pip = 1;
        
        // Taking input
        int n_read = getline(&input_buffer, &len, stdin);
        input_buffer[n_read-1] = '\0';
        add_to_hist(input_buffer, n_read-1);

        // Setting up commands
        command = (cmd *)malloc(sizeof(cmd) * n_read);
        memset(command->arguments, 0, sizeof(command->arguments));        
        bckgrnd = (_Bool *) malloc (sizeof(_Bool) * n_read);
        memset(bckgrnd,0,n_read * sizeof(_Bool));
        cmd_num = parse_input(input_buffer);

        // Setting up pipes
        pipes_setup();

        // Executing commands
        for(int i=0; i<cmd_num; i++){ 
            if(command[i].command != NULL && command[i].command[0] != ' ') execute(i);
        }
        // Resetting variables
        pipes_done();
        free(input_buffer);
        free(command);
    }
    return 0;
}
