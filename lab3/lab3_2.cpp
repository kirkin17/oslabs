#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    pid_t pid_child = fork();
    if (pid_child == 0)
    {
        execvp("lab3_1.cpp", argv);
    }
    else if (pid_child > 0) 
    {
        printf("Идентификатор текущего процесса(2 программа): %d\n", (int)getpid());
        printf("Идентификатор родительского процесса(2 программа): %d\n", (int)getppid());
        printf("Идентификатор дочернего процесса(2 программа): %d\n", (int)pid_child);
        int *status;
        while (waitpid(pid_child, status, WNOHANG) == 0) sleep(0.5);
        printf("Дочерний процесс(pid: %d) завершен с кодом: %d", pid_child , *status);
    }
    else perror("fork");

    
}