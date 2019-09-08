#include "main.h"

// Intialization
void gethd(char *home, int pid);
void init_hist();

// Shell loop
void display_shell();
void execute(int cmd);
void add_to_hist(char *input, int size);

// Parsing
int parse_input(char *input);
int parse_dir(char ** inp, char** dir, char * cmd, char* final);

// Signal related
void signal_setup();
void back_end(int sig);
void back_send(int sig);

// Redirection related
int redirect(cmd command);

// Piping related
void pipes_setup();
void pipes_done();

// Supported commands
void ls(cmd command);
void cd(cmd command);
void echo(cmd command);
void pinfo(cmd command);
void nightswatch(cmd command, _Bool back);
void history(cmd command);
void sys(cmd command, _Bool back);