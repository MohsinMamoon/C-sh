#include "decl.h"
#include "defs.h"

void gethd(char *home, int pid) {
    char s_pid[20], *path, temp1[]="/proc/", temp2[] = "/exe";
    int i;
    sprintf(s_pid, "%d", pid);
    path = strcat(strncat(temp1,s_pid,strlen(s_pid)),temp2);
    realpath(path, home);
    for(i = strlen(home)-1; i>=0; i--) {
        if(home[i] == '/') {
            home[i+1] = 'h';
            home[i+2] = '\0';
            break;
        }
    }
    for(int j=0; j<strlen(home); j++) {
        hist_dir[j] = home_dir[j];
    }
    home[i] = '\0';
}

char* cmp(char* home, char* curr) {
    if(!strncmp(home, curr, strlen(home))) {
        int size =strlen(curr)-strlen(home)+2;
        char tilda[] = "~", *new;
        new = (char*) malloc (size * sizeof(char));
        new[0] = '~';
        for(int i=1; i<size; i++) {
            new[i] = curr[i-1+strlen(home)];
        }
        return new;
    }
    else
    {
        return curr;
    }
    
}

void display_shell() {
    getcwd(cur_dir, sizeof(cur_dir));
    char pc[100], user[100];
    gethostname(pc, 200);
    struct passwd *user_det;
    user_det = getpwuid(getuid());
    char *to_print = cmp(home_dir, cur_dir);
    printf("\e[0;32m%s@%s\e[m:\e[1;34m%s\e[m$ ", user_det->pw_name, pc, to_print);
}