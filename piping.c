#include "defs.h"
#include "decl.h"

void pipes_setup() {
    pipe_fd = (int *) malloc (sizeof(int) * 2 * pipe_no);
    for (int i=0; i<pipe_no; i++){
        pipe(pipe_fd + (2*i));
    }
}

void pipes_done() {
    for(int i=0; i<2*pipe_no; i++) {
        close(pipe_fd[i]);
    }
    free(pipe_fd);
}


void piping_begin(cmd command) {
    if(command.pipe_in != -1 || command.pipe_out != -1) {
        if(command.pipe_in != -1) dup2(pipe_fd[command.pipe_in], 0);
        if(command.pipe_out != -1) dup2(pipe_fd[command.pipe_out], 1);
        for(int i=0; i<2*pipe_no; i++) {
            close(pipe_fd[i]);
        }
    }
    return;
}

void out_close(cmd command) {
    if(command.pipe_out != -1) close(pipe_fd[command.pipe_out]);
    return;
}