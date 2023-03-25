#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <poll.h>

struct targs
{
    int flag;
    char sym;
};

int main()
{
    printf("Программа 1 начала работу\n");
    
       
    sem_t *sem;
    FILE *file;
    
    if((sem = sem_open("/sem", 0)) == SEM_FAILED)
    {
        perror("sem_open");
        if((sem = sem_open("/sem", O_CREAT, 0777, 1)) == SEM_FAILED) perror("sem_open");
        else printf("Семафор создан\n");
    }
    else printf("Семафор открыт\n");

    if((file = fopen("out", "a")) == NULL) perror("fopen");

    targs args{0, '1'};

    while(args.flag == 0)
    {
        sem_wait(sem);
        for(int i = 0; i < 5; i++)
        {
            fputc(args.sym, file);
            fflush(file);
            fputc(args.sym, stdout);
	        fflush(stdout);
            sleep(1);
        }
        sem_post(sem);
        sleep(1);

        pollfd pfd[1];
        pfd[0].fd = STDIN_FILENO;
        pfd[0].events = POLLIN;
        poll(pfd, 1, 0);
        if((pfd[0].revents == POLLIN)) args.flag = 1;
    }
    fclose(file);
    sem_close(sem);
    sem_unlink("sem");
    printf("\nПрограмма 1 закончила работу\n");
}