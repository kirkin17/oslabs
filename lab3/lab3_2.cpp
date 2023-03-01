#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <chrono>
#include <iomanip>
#include <string.h>

std::string time_in_HH_MM_SS_MMM()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = system_clock::to_time_t(now);
    std::tm bt = *std::localtime(&timer);
    std::ostringstream oss;
    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

int main(int argc, char *argv[])
{
    printf("Программа 2 начала работу\n");
    pid_t pid_child = fork();

    if (pid_child == 0)
    {
        const char *program = "lab3_1";                          //название программы
        std::string PATH = (std::string)getenv("PATH");
        PATH = (std::string)get_current_dir_name() + ":" + PATH;
        std::string path = "";
        for(int i = 0; i <= PATH.size(); i++)
        {
            if(PATH[i] == ':' || i == PATH.size())
            {
                path = path + "/" + program;
                if(execvp(path.c_str(), argv) != 0)
                {
                    path = "";
                    continue;
                }
            }
            else path.push_back(PATH[i]);
        }
        perror("execvp");
    }
    else if (pid_child > 0) 
    {
        printf("Идентификатор текущего процесса(2 программа): %d\n", (int)getpid());
        printf("Идентификатор родительского процесса(2 программа): %d\n", (int)getppid());
        printf("Идентификатор дочернего процесса(2 программа): %d\n", (int)pid_child);
        int status;
        while (waitpid(pid_child, &status, WNOHANG) == 0)
        {
            printf("%s\n", time_in_HH_MM_SS_MMM().c_str());
            usleep(500000);
            printf("%s\n", time_in_HH_MM_SS_MMM().c_str());
        }
        printf("Дочерний процесс(pid: %d) завершен с кодом: %d\n", pid_child , status);
    }
    else perror("fork");
    printf("Программа 2 завершила работу\n");
}