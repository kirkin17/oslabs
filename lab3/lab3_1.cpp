#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    printf("Идентификатор текущего процесса(1 программа): %d\n", (int)getpid());
    printf("Идентификатор родительского процесса(1 программа): %d\n", (int)getppid());
    while(1)
    {
        for(int i = 0; i < argc; i++)
        {
            printf("%s\n", argv[i]);
            sleep(1);
        }
    }
    exit(2);
}
