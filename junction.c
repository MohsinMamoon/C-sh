#include "decl.h"
#include "defs.h"

void execute(int cmd)
{
   // Redirection Setup
   if (command[cmd].in_redir || command[cmd].out_redir){
      if(!redirect(command[cmd])){
         dup2(orig_stdin, 0);
         dup2(orig_stdout, 1);
         return;
      }
   }

   // Clear Screen
   if (!strcmp(command[cmd].command, "clear") || command[cmd].command[0] == '\f') {
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
      jobs:
         syntax: jobs
   */
  else if(!strcmp(command[cmd].command, "jobs")) {
   jobs(command[cmd]);
  }

  /*
      kjob:
         syntax: kjob [job] [signal]
         [job]: job number from jobs
         [signal]: signal number
   */
  else if(!strcmp(command[cmd].command, "kjob")) {
     kjob(command[cmd]);
  }

   /*
      fg:
         syntax: fg [job]
         [job]: if not given, last job will be considered
   */
   else if(!strcmp(command[cmd].command, "fg")) {
      fg(command[cmd]);
   }

   /*
      bg:
         syntax: bg [job]
         [job]: if not given, last job will be considered
   */
   else if(!strcmp(command[cmd].command, "bg")) {
      bg(command[cmd]);
   }

   /*
      overkill: 
            syntax: overkill
   */
  else if(!strcmp(command[cmd].command, "overkill")) {
     overkill();
  }
   /*
      Up arrows:
   */
   else if(command[cmd].command[0] == '\033') {
      int up_arr = 0, start=0, size=0;
      char s[5];
      for(int i=2; i<strlen(command[cmd].command); i += 3){
         if(command[cmd].command[i] == 'A') up_arr++;
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
      write(1, &his[start], size);
      return;
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
