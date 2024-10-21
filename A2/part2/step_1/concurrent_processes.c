#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void process1()
{
    while (1)
    {
        printf("I am Process 1\n");
        sleep(1);
    }
}

void process2()
{
    while (1)
    {
        printf("I am Process 2\n");
        sleep(1);
    }
}

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) // Child process
    {
        process1();
    }
    else // Parent process
    {
        process2();
    }

    return 0;
}