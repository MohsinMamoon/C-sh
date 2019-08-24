#include "defs.h"
#include "decl.h"

void init_hist() {
    if(access(hist_dir, F_OK) == -1) {
        his_fd = fopen(hist_dir, "a+");
        fprintf(his_fd, "%d\n", his_num);
        fclose(his_fd);
    }
}

void load_hist() {
    his_fd = fopen(hist_dir, "r+");
    fseek(his_fd, 0, SEEK_SET);
    fscanf(his_fd, "%d", &his_num);
    fseek(his_fd, 1, SEEK_CUR);
    fscanf(his_fd, "%[^\n]s", his);
    fclose(his_fd);
}

void store_hist() {
    his_fd = fopen(hist_dir, "w+");
    fseek(his_fd, 0, SEEK_SET);
    fprintf(his_fd, "%d\n", his_num);
    fprintf(his_fd, "%s", his);
    fprintf(his_fd, "\n");
    fclose(his_fd);
}

void add_to_hist(char *input, int size) {
    load_hist();
    int i,j;
    if(his_num >= 20) {
        int sep_ind;
        for(int k=0;;k++) {
            if(his[k] == '|') {
                sep_ind = k;
                break;
            }
        }
        for(i=sep_ind; i<strlen(his); i++) {
            his[i-sep_ind] = his[i+1];
        }
        for(i=strlen(his), j=0; j < size; i++, j++) {
            if(i>20000) {
                fprintf(stderr, "History Memory overloaded! Exiting!\n");
                exit(1);
            }
            his[i] = input[j];
        }
        his[i++] = '|';
        his[i] = '\0';
    }
    else {
        his_num++;
        for(i=strlen(his), j=0; j< size; i++, j++) {
            his[i] = input[j];
        }
        his[i] = '|'; 
    }
    store_hist();
}

void history(cmd command) {
    load_hist();
    int num = -1, start=0, print = 21;
    if(command.arguments[0] != NULL) {
        if(sscanf(command.arguments[0], "%d", &num) <= 0) {
            printf("Invalid input number! Defaulting to 10");
            num = 10;
        }
    }
    if (num <= 0 || num > 20) num = 10;
    print = print-num;
    for(int i=0, j=strlen(his)-2;; j--) {
        if(his[j] == '|') i++;
        if(j == 0 || i == num) {
            start = j;
            break;
        }
    }
    char *ptr = &his[start], delim[] = "|", *token, *save_ptr;
    for(;;ptr = NULL) {
        token = strtok_r(ptr, delim, &save_ptr);
        if(token == NULL) break;
        printf("%d: %s\n", print++, token);
    }
}
