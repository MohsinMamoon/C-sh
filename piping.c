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