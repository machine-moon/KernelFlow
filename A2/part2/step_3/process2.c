#include <stdio.h>
#include <unistd.h>

int main()
{
    for (int i = 0; i < 10; i++)
    {
        printf("I am Process 2\n");
        sleep(1);
    }

    return 0;
}