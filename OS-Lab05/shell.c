#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

//Function to splitthe input on whitespace
char **split_input(char *input){
    char **args = malloc(MAX_INPUT_LENGTH * sizeof(char *));
    int arg_count = 0;
    char *token;
    const char *delim = "\t\n";

    token = strtok(input, delim);

    while(token !=NULL){
        args[arg_count++] = token;
        token = strtok(NULL, delim);
    }
    args[arg_count] = NULL;
    return args;

}

int main (){
    char input[MAX_INPUT_LENGTH];
    
    while(1) {
        printf("Enter a command: ");
        if(fgets(input,MAX_INPUT_LENGTH,stdin) == NULL)
        {
            perror("fgets");
            exit(1);
        }

        pid_t pid = fork();
        if(pid == 0){
            //Child process
            char **args = split_input(input);
            execvp(args[0], args);
            exit(1);
        
        } else if(pid > 0){
            //Parent process
            int status;
            waitpid(pid, &status, 0);
        
        } else {
            perror("fork");
            exit(1);
        }
    }

    return 0;
}


