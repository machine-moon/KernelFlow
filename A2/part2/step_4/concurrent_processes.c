#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 0x1234 // Fixed key for shared memory

/**
 * Function to be executed by Process 1.
 * Generates random numbers and writes them to shared memory.
 * Forks Process 2 if the random number is 9.
 * Terminates if the random number is 0.
 *
 * @param shared_var Pointer to the shared memory variable.
 */
void process1(int *shared_var)
{
    srand(time(0)); // Seed the random number generator
    while (1)
    {
        int randNum = rand() % 11;
        *shared_var = randNum;
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
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("Fork failed");
                exit(1);
            }
            else if (pid == 0)
            {
                execlp("./process2", "process2", NULL);
            }
        }
        if (randNum == 0)
        {
            break;
        }
        sleep(1);
    }
}

int main()
{
    /**
     * shmget - Allocates a shared memory segment.
     *
     * @param SHM_KEY: Key to identify the shared memory segment.
     * @param sizeof(int): Size of the shared memory segment in bytes.
     * @param 0666 | IPC_CREAT: Permissions and flags. 0666 means read and write permissions for
     * @return: Returns the shared memory ID on success, or -1 on failure.
     */
    int shmid = shmget(SHM_KEY, sizeof(int), 0666 | IPC_CREAT);
    if (shmid < 0)
    {
        perror("shmget failed");
        exit(1);
    }

    /**
     * shmat - Attaches the shared memory segment to the calling process.
     *
     * @param shmid: Shared memory ID returned by shmget.
     * @param NULL: Address at which to attach the shared memory segment. NULL lets the system choose the address.
     * @param 0: Flags. 0 means read and write permissions.
     * @return: Returns a pointer to the shared memory segment on success, or -1 on failure.
     */
    int *shared_var = (int *)shmat(shmid, NULL, 0);
    if (shared_var == (void *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // pass the shared memory variable to process1
        process1(shared_var);
    }
    else
    {
        // wait for process1 to finish
        wait(NULL);

        // shmdt - Detaches the shared memory segment from the calling process.
        shmdt(shared_var);
        /**
         * shmctl - Performs control operations on the shared memory segment.
         *
         * @param shmid: Shared memory ID returned by shmget.
         * @param IPC_RMID: Command to remove the shared memory segment.
         * @param NULL: Ignored.
         */
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}