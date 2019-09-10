#include "defs.h"
#include "decl.h"

void get_env(cmd command) {
    if (command.arguments[1] != NULL) {
        fprintf(stderr, "Error: Too many arguments!\n");
        return;
    }
    else if (command.arguments[0] == NULL) {
        fprintf(stderr, "Error: Too few arguments!\n");
        return;
    }
    char *value = getenv(command.arguments[0]);
    if (value == NULL) {
        fprintf(stderr, "Variable %s not set!\n", command.arguments[0]);
    }
    else {
        printf("%s = %s\n", command.arguments[0], value);
    }
    return;
}

void set_env(cmd command) {
    if(command.arguments[2] != NULL) {
        fprintf(stderr, "Error: Too many arguments!\n");
        return;
    }
    else if(command.arguments[0] == NULL) {
        fprintf(stderr, "Error: Too few arguments!\n");
        return;
    }
    if(command.arguments[1] == NULL) command.arguments[1] = "\0";
    if(setenv(command.arguments[0], command.arguments[1], 1) == 0) {
        fprintf(stderr, "%s set to %s\n", command.arguments[0], (command.arguments[1][0] =='\0') ? "Empty String" : command.arguments[1]);
    }
    else {
        fprintf(stderr, "Error: Could not set the variable!\n");
    }
    return;
}

void unset_env(cmd command) {
    if(command.arguments[1] != NULL) {
        fprintf(stderr, "Error: Too many arguments!\n");
        return;
    }
    else if(command.arguments[0] == NULL) {
        fprintf(stderr, "Error: Too few arguments!\n");
        return;
    }
    if(unsetenv(command.arguments[0]) == 0) {
        fprintf(stderr, "%s unset\n", command.arguments[0]);
    }
    else {
        fprintf(stderr, "Error: Could not unset variable!\n");
    }
    return;
}