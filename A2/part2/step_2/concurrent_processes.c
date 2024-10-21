#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

void process1()
{
    srand(time(0));
    while (1)
    {
        int randNum = rand() % 11;
        printf("I am Process 1, Random Number: %d\n", randNum);
        if (randNum > 5)
        {
            printf("High value\n");
        }
        else
        {
            printf("Low value\n");
        }
        if (randNum == 9)
        {
            execlp("./process2", "process2", NULL);
        }
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
    else if (pid == 0)
    {
        process1();
    }
    else
    {
        wait(NULL);
    }

    return 0;
}