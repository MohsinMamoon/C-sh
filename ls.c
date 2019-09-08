#include "defs.h"
#include "decl.h"

_Bool a_flag, l_flag;

char * grpname(struct group *grp) {
    return grp->gr_name;
}

char * usrname(struct passwd *usr) {
    return usr->pw_name;
}

void p_ls(char *name, struct stat st) {
    char perms[10];
    perms[0] = (S_ISDIR(st.st_mode) ? 'd' : '-');
    perms[1] = (S_IRUSR & st.st_mode ? 'r' : '-');
    perms[2] = (S_IWUSR & st.st_mode ? 'w' : '-');
    perms[3] = (S_IXUSR & st.st_mode ? 'x' : '-');
    perms[4] = (S_IRGRP & st.st_mode ? 'r' : '-');
    perms[5] = (S_IWGRP & st.st_mode ? 'w' : '-');
    perms[6] = (S_IXGRP & st.st_mode ? 'x' : '-');
    perms[7] = (S_IROTH & st.st_mode ? 'r' : '-');
    perms[8] = (S_IWOTH & st.st_mode ? 'w' : '-');
    perms[9] = (S_IXOTH & st.st_mode ? 'x' : '-');
    for(int i=0; i<10; i++) printf("%c", perms[i]); 
    char *time =  ctime(&st.st_mtime);
    time[strlen(time)-9] = '\0';
    printf(" %ld %s %s %5ld %s %s\n", st.st_nlink, usrname(getpwuid(st.st_uid)), grpname(getgrgid(st.st_gid)), st.st_size, &time[4], name);
    return;
}

void show_dir(DIR *D,char *path) {
    struct dirent *d;
    while((d = readdir(D)) != NULL) {
        if(!(a_flag) && (d->d_name[0] == '.')) continue;
        if(!l_flag) printf("%s\t", d->d_name);
        else {
            char file[1000];
            int i=0;
            if(path[0] != '.' && strlen(path) != 1) {
                for(i=0; i<strlen(path); i++) file[i] = path[i];
            }
            if(i!=0) file[i++] = '/';
            for(int j=0; j<strlen(d->d_name); j++) file[i++] = d->d_name[j];
            file[i] = '\0';
            struct stat st;
            stat(file, &st);
            p_ls(d->d_name, st);
        }
    }
}

void ls(cmd command) {
    int pid = fork();
    if(pid) {
        if(command.pipe_out != -1) close(pipe_fd[command.pipe_out]);

        wait(NULL);
    }
    else if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, back_send);
        
        if(command.pipe_in != -1 || command.pipe_out != -1) {
            if(command.pipe_in != -1) dup2(pipe_fd[command.pipe_in], 0);
            if(command.pipe_out != -1) dup2(pipe_fd[command.pipe_out], 1);
            for(int i=0; i<2*pipe_no; i++) {
                close(pipe_fd[i]);
            }
        }
        
        char *dir[1000], temp[8000];
        memset(temp, 0, sizeof(temp));
        temp[0] = '-';
        memset(dir, 0, sizeof(dir));
        int mode = parse_dir(command.arguments, dir, "ls", temp);

        switch (mode)
        {
        case 0:
            a_flag = 0;
            l_flag = 0;
            break;
        case 1:
            a_flag = 0;
            l_flag = 1;
            break;
        case 2:
            a_flag = 1;
            l_flag = 0;
            break;
        case 3:
            a_flag = 1;
            l_flag = 1;
            break;
        default:
            break;
        }

        if(dir[0] == NULL) {
            dir[0] = ".";
            temp[0] = '-';
            temp[1] = '.';
            temp[2] = '-';
            temp[3] = '\0';
        }

        char *ptr1 = temp, *token, *save_ptr, delim[] = "-";
        int i=0;
        for(;; i++, ptr1 = NULL) {
            token = strtok_r(ptr1, delim, &save_ptr);
            if(token == NULL) break;

            struct stat st;

            if(!strcmp(dir[i], "W_PATH") || stat(dir[i], &st)) {
                fprintf(stderr, "ls: could not access: File or Directory does not exist!\n");
                continue;
            }
            printf("\n");
            if(S_ISDIR(st.st_mode)) {
                if(dir[1] != NULL) printf("%s:\n", token);
                DIR *D = opendir(dir[i]);
                show_dir(D, dir[i]);
                closedir(D);
            }
            else {
                if(!l_flag) printf("%s\n", token);
                p_ls(token, st);            
            }
            printf("\n\n");
        }
        exit(0);
    }
    else {
        fprintf(stderr, "Fork Error!\n");
        return;
    }
}
