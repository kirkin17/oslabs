#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct targs
{
    int flag;
    char sym;
};

void* proc1(void *arg)
{
    printf("Поток 1 начал работу\n");
    targs *args = (targs*)arg;
    while(args->flag == 0)
    {
        putchar(args->sym);
	    fflush(stdout);
        sleep(1);
    }
    printf("Поток 1 закончил работу\n");
    pthread_exit((void*)2);
}

void* proc2(void *arg)
{
    printf("Поток 2 начал работу\n");
    targs *args = (targs*)arg;
    while(args->flag == 0)
    {
        putchar(args->sym);
	    fflush(stdout);
        sleep(1);
    }
    printf("Поток 2 закончил работу\n");
    pthread_exit((void*)2);
}

int main()
{
    printf("Программа начала работу\n");

    targs arg1, arg2;
    arg1.flag = 0;
    arg1.sym = '1';
    arg2.flag = 0;
    arg2.sym = '2';

    pthread_t id1, id2;
    pthread_create(&id1, NULL, proc1, &arg1);
    pthread_create(&id2, NULL, proc2, &arg2);
    printf("Программа ждет нажатия клавиши\n");
    getchar();
    printf("Клавиша нажата\n");
    arg1.flag = 1;
    arg2.flag = 1;

    pthread_cancel(id1);
    pthread_cancel(id2);
    
    int *exitcode1;
    int *exitcode2;

    pthread_join(id1, (void**)&exitcode1);
    pthread_join(id2, (void**)&exitcode2);
    printf("Поток 1 был завершен с кодом: %p\n", exitcode1);
    printf("Поток 2 был завершен с кодом: %p\n", exitcode2);
    printf("Программа закончила работу\n");
}