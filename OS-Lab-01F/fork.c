#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int x= 100;
    pid_t pid;
    int fd;

    printf("Before fork(), x = %d\n", x);

    //Question 2
    fd = open("example.txt", O_CREAT | O_RDWR, 0644);
    if (fd ==-1){
        printf("Error opening file\n");
        return 1;
    }

    pid = fork();

    if(pid == 0) {
        //Child process
        printf("Child process:writing to file\n");
        x = 200;
        write(fd,"Hello from the child process\n", 24);
        close(fd);
        printf("Child process: x = %d\n", x);
    } else if (pid > 0) {
        //Parent process
        wait(NULL);
        printf("Parent process:writing to file\n");
        x = 300;
        write(fd,"Hello from the parent process\n", 24 ); 
        close(fd);
        printf("Parent process: x = %zd\n", write(fd, "Hello from parent process\n", 25));
    } else {
        //fork() failed
        printf("Fork Failed\n");
        return 1;    
        }

        return 0; 
}
