
/********************************************************************
 * Twitter Stream Manager
 *
 * Graeme Lyon
 * March 2014
********************************************************************/
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    pid_t cpid, pid;
    int status;
    cpid = fork();

    for (;;)
    {
        switch (cpid)
        {
        case -1 : //Fork failure
            exit(EXIT_FAILURE);
            break;

        case 0 : //Child Process
            printf("Child process %ld\n", (long) getpid());
            execlp("java", "java", "-jar", "TwitterStreamListener.jar", NULL);
            sleep(1); //debug
            return 0; //exit child process
            break;

        default : //Parent process
            printf("Parent process %ld\n", (long) getpid());
            while ((pid = waitpid(-1, NULL, WNOHANG)) != -1);

            printf("Starting new child\n\n");
            cpid = fork(); //restart
            break;
        }
    }
}
