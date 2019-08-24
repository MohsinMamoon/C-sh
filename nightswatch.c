#include "decl.h"
#include "defs.h"

char get_key()
{
	char c;
	struct timeval tv;
	fd_set fs;
	tv.tv_usec = tv.tv_sec = 0;
 
	FD_ZERO(&fs);
	FD_SET(STDIN_FILENO, &fs);
 
	if (select(STDIN_FILENO + 1, &fs, 0, 0, &tv)) {
		c = getchar();
	}
	return c;
}

void interrupt(int time) {
    char header[1000], line[1000];
    int start;
    FILE *f;
    f = fopen("/proc/interrupts", "r");
    fscanf(f, "%[^\n]s", header);
    for(start=0; ;start++) if(header[start] =='C') break;
    printf("%s\n", &header[start]);
    fclose(f);

    while(1) {

        f = fopen("/proc/interrupts", "r");
        fseek(f, 0, SEEK_SET);
        for(int i=0; i<3; i++){
            int read = fscanf(f, "%[^\n]s", line);
            fseek(f, read, SEEK_CUR);
        }
        for(int i=0; i<strlen(line); i++) {
            if(line[i] == 'I') {
                line[i] = '\n';
                line[i+1] = '\0';
                break;
            }
        }
        printf("%s\n", &line[start]);
        fclose(f);
        if(get_key() == 'q') return;
        sleep(time);
    }
    return;
}

void dirty(int time) {
    char mem[1000];
    int start;
    FILE *f;
    while(1) {
        f = fopen("/proc/meminfo", "r");
        fseek(f, 0, SEEK_SET);
        while(1) {
            int read = fscanf(f, "%[^\n]s", mem);
            fseek(f, read, SEEK_CUR);
            if(!strncmp(mem, "Dirty:", 6)) break;
        }
        for(start=6; ;start++) if(mem[start] != ' ') break;
        printf("%s\n", &mem[start]);
        fclose(f);
        if(get_key() == 'q') return;
        sleep(time);
    }
    return;
}

struct termios orig, modif;
void nightswatch (cmd command, _Bool back) {
    int mode = 1, time;
    if(command.arguments[0] == NULL || command.arguments[1] == NULL || command.arguments[2] == NULL || strcmp(command.arguments[0],"-n")) mode = 0;
    else if(sscanf(command.arguments[1], "%d", &time) < 0) mode = 0;

    if(mode != 0 && !strcmp(command.arguments[2], "interrupt"))mode = 1;
    else if(mode != 0 && !strcmp(command.arguments[2], "dirty"))mode = 2;
    else mode = 0;

    if(mode == 0) {
        printf("Invalid arguments! Usage: nightswatch -n <seconds> <command>\n");
        return;
    }
    else{


        int pid = fork();

        if(pid != 0) {
            if(!back){ 
                tcgetattr(0, &orig);
                modif = orig;
                modif.c_lflag &= ~ICANON;
                tcsetattr(0, TCSANOW, &modif);
                wait (NULL);
                tcsetattr(0, TCSANOW, &orig);
            }
        }
        else if(pid == 0) {
            if(back) setpgid(0,0);
            if(mode == 1) interrupt(time);
            else dirty(time);
            exit(1);
        }
        return;
    }
}