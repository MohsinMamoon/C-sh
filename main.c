#include "decl.h"
#include "defs.h"
// #include "main.h"   
// #include "junction.h"

int main()
{
    gethd(home_dir, getpid());
    while (1)
    {
        display_shell();

        char *input_buffer = NULL;
        size_t len = 0;
        int n_read = getline(&input_buffer, &len, stdin);
        input_buffer[strlen(input_buffer)-1] = '\0';
        command = (cmd *)malloc(sizeof(cmd) * n_read);
        bckgrnd = (_Bool *) malloc (sizeof(_Bool) * n_read);
        cmd_num = parse_input(input_buffer);

        printf("%d commands in total\n", cmd_num);
        write(1, "\n", 1);
        for (int i = 0; i < cmd_num; i++)
        {
            printf("Command No: %d\n", i+1);
            printf("\t\tName: %s\n\t\tArguments: ", command[i].command);
            fflush(stdout);
            for (int j=0; command[i].arguments[j] != NULL; j++) {
                write(1, command[i].arguments[j], strlen(command[i].arguments[j]));
                write(1, "\n\t\t ", 4);
            }
            write(1, "\n", 1);

        }
        for(int i=0; i<cmd_num; i++) execute(i);
        free(input_buffer);
        free(command);
    }
    return 0;
}
