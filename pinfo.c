#include "decl.h"
#include "defs.h"

void pinfo(cmd command) {
    char home[1000], s_pid[20], memory[100], stat_path[1000], stat_in[1000], exec_path[]="/proc/", temp2[] = "/stat", temp3[] = "/exe", p_status;
    memset(stat_path, 0, sizeof(stat_path));
    size_t len = 0;
    if(command.arguments[0] == NULL) {
        int pid = getpid();
        sprintf(s_pid, "%d", pid);
    }
    else {
        for(int i=0; ;i++) {
            s_pid[i] = command.arguments[0][i];
            if(s_pid[i] == '\0') break;
        }
    }
    strncat(exec_path,s_pid,strlen(s_pid));
    strncpy(stat_path, exec_path, strlen(exec_path));
    strcat(exec_path, temp3);
    strcat(stat_path, temp2);
    realpath(exec_path, home);

    FILE  *file = fopen(stat_path, "r");
    int spaces = 0;
    while(spaces < 23) {
        fscanf(file, "%s", stat_in);
        if(spaces == 2) p_status = stat_in[0];
        if(spaces == 22) for(int i=0; i<strlen(stat_in); i++) memory[i] = stat_in[i];
        spaces ++;
    }
    printf("pid: %s\nProcess Status: %c\nMemory: %s\nExecutable Path: %s\n\n", s_pid, p_status, memory, home);
    fclose(file);
    return;
}
