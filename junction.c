#include "decl.h"
#include "defs.h"

void execute(int cmd)
{
   // fg commmand (Beta version)
   if(!strncmp(command[cmd].command, "fg", 2)) {
      signal(SIGTTOU, SIG_IGN);
      int pid;
      sscanf(command[cmd].arguments[0], "%d", &pid);
      setpgid(pid, tcgetpgrp(0));
      tcsetpgrp(0, pid);
      kill(pid, SIGCONT);
      wait(NULL);
      tcsetpgrp(0, getpid());
      signal(SIGTTOU, SIG_DFL);
   }

   // Redirection Setup
   if (command[cmd].in_redir || command[cmd].out_redir){
      if(!redirect(command[cmd])){
         dup2(orig_stdin, 0);
         dup2(orig_stdout, 1);
         return;
      }
   }

   // Clear Screen
   if (!strcmp(command[cmd].command, "clear")) {
      printf("\e[1;1H\e[2J");
   }

   // Quit the terminal 
   else if (!strcmp(command[cmd].command, "quit") || !strcmp(command[cmd].command, "exit") || (strlen(command[cmd].command) == 1 && command[cmd].command[0] == 'q')) {
      exit(0);
   }

   /*
      ls: 
         syntax: ls [options] [files/directory]
         [options]: -l, -a, -al
         [files/directory]: file/directory names with spaces also supported (enclose in "")
   */
   else if (!strcmp(command[cmd].command, "ls")) {
      ls(command[cmd]);
   }

   /*
      cd:
         syntax: cd [directory]
         [directory]: directory names with spaces also supported (enclose in "")
   */
   else if (!strcmp(command[cmd].command, "cd")) {
      cd(command[cmd]);
   }

   /*
      echo: 
         syntax: echo [string]
   */
   else if (!strcmp(command[cmd].command, "echo")) {
      echo(command[cmd]);
   }

   /*
      pwd:
         syntax: pwd
   */
   else if (!strcmp(command[cmd].command, "pwd")) {
      getcwd(cur_dir, sizeof(cur_dir));
      fprintf(stderr, "Present Working Directory: %s\n\n", cur_dir);
   }

   /*
      pinfo:
         syntax: pinfo [pid]
         [pid]: if pid is not given, pid of shell will be taken
   */
   else if (!strcmp(command[cmd].command, "pinfo")) {
      pinfo(command[cmd]);
   }

   /*
      nightswatch:
               syntax: nightswatch -n [num_of_seconds] [function]
               [num_of_seconds]: delay in output (in seconds)
               [function]: dirty or interrupt
   */
   else if (!strcmp(command[cmd].command, "nightswatch")) {
      nightswatch(command[cmd], bckgrnd[cmd]);
   }

   /*
      history:
            syntax: history [num]
            [num]: between 1 and 20 (if out range, will be defaulted to 10)
   */
   else if (!strcmp(command[cmd].command, "history")) {
      history(command[cmd]);
   }

   /* 
      all other shell commands:
         syntax: syntax of respective commands
   */
   else {
      sys(command[cmd], bckgrnd[cmd]);
   }

   // Resetting stdin and stdout
   if (command[cmd].in_redir || command[cmd].out_redir){
      dup2(orig_stdin, 0);
      dup2(orig_stdout, 1);
   }
}
