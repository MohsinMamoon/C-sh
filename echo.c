#include "decl.h"
#include "defs.h"

void echo(cmd command) {
    int pid = fork();

    if(pid) {
        out_close(command);
        wait(NULL);
    }    
    else if(pid == 0) {
        
        piping_begin(command);

        int i = 0;
        while (command.arguments[i] != NULL) {
            printf("%s ", command.arguments[i]);
            i++;
        }
        printf("\n");
        exit(0);
    }
    else {
        fprintf(stderr, "Forking error!\n");
        return;
    }
}