#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (){
    int pipefd [2];

    if (pipe(pipefd) == -1 ){
        perror("pipe");
        exit (1);
    }
     
    pid_t pid = fork ();

    if (pid == 0 ){
        close(pipefd[0]);

        char message [] = "Hello from child!";
        if (write(pipefd[1], message, sizeof(message)) == -1){
            perror("Write ");
           exit(1);  
           
        }
       
        else {
            //parent process
            close (pipefd[1]);
        }
        char buffer [1024];
        ssize_t bytesRead = read(pipefd[0] , buffer, sizeof(buffer));
        if (bytesRead == -1){
            perror ("read");
            exit(1);
        }
        else if(bytesRead == 0)
        printf("Message from the child process: %s " , buffer);
        close(pipefd[0]);
        wait (NULL);

        return 0;
    }
}