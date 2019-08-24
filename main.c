#include "decl.h"
#include "defs.h"

int main()
{   
    signal(SIGCHLD, back_end);
    printf("\e[1;1H\e[2J");         
    gethd(home_dir, getpid());
    init_hist();

    while (1)
    {

        display_shell();
        
        char *input_buffer = NULL;
        size_t len = 0;
        int n_read = getline(&input_buffer, &len, stdin);
        input_buffer[n_read-1] = '\0';
        add_to_hist(input_buffer, n_read-1);
        command = (cmd *)malloc(sizeof(cmd) * n_read);
        memset(command->arguments, 0, sizeof(command->arguments));        
        bckgrnd = (_Bool *) malloc (sizeof(_Bool) * n_read);
        memset(bckgrnd,0,n_read * sizeof(_Bool));
        cmd_num = parse_input(input_buffer);
        for(int i=0; i<cmd_num; i++) if(command[i].command != NULL && command[i].command[0] != ' ') execute(i);
       
        free(input_buffer);
        free(command);
    }
    return 0;
}
