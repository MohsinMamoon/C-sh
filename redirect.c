#include "defs.h"
#include "decl.h"

int redirect(cmd command) {
    orig_stdin = dup(0);
    orig_stdout = dup(1);

    if(command.in_redir) {
        char **dir, **in_file;
        dir = (char **) malloc(sizeof(char *));
        in_file = (char **) malloc(sizeof(char *));
        dir[0] = NULL;
        in_file[0] = command.in;
        parse_dir(in_file, dir, "redir", (char *)NULL);
        struct stat st;
        if(stat(dir[0], &st) != 0) {
            fprintf(stderr, "Redirection error: Input file does not exist!\n");
            return 0;
        }
        else if(!S_ISREG(st.st_mode)) {
            fprintf(stderr, "Redirection error: Input file is not a regular file!\n");
            return 0;
        }
        int redirect_in = open(dir[0], O_RDONLY);
        if(redirect_in == -1) {
            fprintf(stderr, "Redirection error: Input file could not be accessed!\n");
            return 0;
        }
        dup2(redirect_in, 0);
        free(dir);
        free(in_file);
    }
    
    if(command.out_redir) {
        char **dir, **out_file;
        dir = (char **) malloc(sizeof(char *));
        out_file = (char **) malloc(sizeof(char *));
        dir[0] = NULL;
        out_file[0] = command.out;
        parse_dir(out_file, dir, "redir", (char *)NULL);
        struct stat st;
        if(stat(dir[0], &st) == 0 && !S_ISREG(st.st_mode)) {
            fprintf(stderr, "Redirection error: Output file is not a regular file!\n");
            return 0;
        }
        
        int redirect_out;
        if(command.append) redirect_out = open(dir[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else redirect_out = open(dir[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(redirect_out == -1) {
            fprintf(stderr, "Redirection error: Output file could not be accessed!\n");
            return 0;
        }
        dup2(redirect_out, 1);
        free(dir);
        free(out_file);
    }

    return 1;
}