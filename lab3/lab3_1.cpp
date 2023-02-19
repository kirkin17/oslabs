#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    printf("Программа 1 начала работу\n");
    printf("Идентификатор текущего процесса(1 программа): %d\n", (int)getpid());
    printf("Идентификатор родительского процесса(1 программа): %d\n", (int)getppid());
    for(int j = 0; j < 5; j++)
    {
        for(int i = 0; i < argc; i++)
        {
            printf("%s\n", argv[i]);
            sleep(1);
        }
    }
    printf("Программа 1 завершила работу\n");
    exit(EXIT_SUCCESS);
}
