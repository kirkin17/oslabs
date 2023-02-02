#include <iostream>
#include <thread>
using namespace std;

typedef struct
{
    int flag;
    char sym;
} targs;

void* proc1(void *arg)
{
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL); //режим отложенного досрочного завершения
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL); //поток завершать нельзя, вход в критическое место
    cout << "Поток 1 начал работу\n";
    targs *args = (targs*)arg;
    while(args->flag == 0)
    {
        putchar(args->sym);
	    fflush(stdout);
        std::this_thread::sleep_for(1s);
    }
    cout << "Поток 1 закончил работу\n";
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); //можно завершать поток
    pthread_testcancel(); //точка останова(проверка был ли поток остановлен извне)
}

void* proc2(void *arg)
{
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL); //режим отложенного досрочного завершения
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL); //поток завершать нельзя, вход в критическое место
    cout << "Поток 2 начал работу\n";
    targs *args = (targs*)arg;
    while(args->flag == 0)
    {
        putchar(args->sym);
	    fflush(stdout);
        std::this_thread::sleep_for(1s);
    }
    cout << "Поток 2 закончил работу\n";
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); //можно завершать поток
    pthread_testcancel(); //точка останова(проверка был ли поток остановлен извне)
}

int main()
{
    cout << "Программа начала работу\n";

    targs arg1, arg2;
    arg1.flag = 0;
    arg1.sym = '1';
    arg2.flag = 0;
    arg2.sym = '2';

    pthread_t id1, id2;
    pthread_create(&id1, NULL, proc1, &arg1);
    pthread_create(&id2, NULL, proc2, &arg2);
    cout << "Программа ждет нажатия клавиши\n";
    getchar();
    cout << "Клавиша нажата\n";
    arg1.flag = 1;
    arg2.flag = 1;

    void *exitcode1;
    void *exitcode2;

    pthread_cancel(id1);
    pthread_cancel(id2);
    
    pthread_join(id1, &exitcode1);
    pthread_join(id2, &exitcode2);
    if (exitcode1 == PTHREAD_CANCELED) cout << "Поток 1 был отменен c кодом: " << exitcode1 << endl;
    if (exitcode2 == PTHREAD_CANCELED) cout << "Поток 2 был отменен c кодом: " << exitcode2 << endl;
    cout << "Программа закончила работу\n";
}