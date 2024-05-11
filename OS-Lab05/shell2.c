#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

//Function to split the input on whitespace
char **split_input(char *input){
    char **args = malloc(MAX_INPUT_LENGTH * sizeof(char *));
    if (args == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int arg_count = 0;
    char *token;
    const char *delim = " \t\n";
    char *saveptr;

    token = strtok_r(input, delim, &saveptr);

    while(token != NULL){
        args[arg_count++] = token;
        token = strtok_r(NULL, delim, &saveptr);
    }
    args[arg_count] = NULL;
    return args;
}

int main (){
    char input[MAX_INPUT_LENGTH];
    
    while(1) {
        printf("Enter a command: ");
        if(fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }


        //Base Case for cd command

        char **args = split_input(input);

        if (strcmp(args[0], "cd") == 0){
            if(args[1] == NULL) {
                fprintf(stderr, "cd:expected argument\n");
            } else {
                if(chdir(args[1])!= 0) {
                    perror("cd");
                }
            }
            free(args);
            continue;
        }

        pid_t pid = fork();
        if(pid == 0){
            //Child process
            char **args = split_input(input);
            execvp(args[0], args);
            perror("execvp"); // Print error if execvp fails
            exit(EXIT_FAILURE);
        } else if(pid > 0){
            //Parent process
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        free(args);
    }

    return 0;
}