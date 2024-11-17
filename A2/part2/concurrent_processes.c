#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 0x1234 // Fixed key for shared memory
#define SEM_KEY 0x5678 // Fixed key for semaphore

/**
 * Function to perform semaphore operations.
 *
 * @param semid Semaphore ID.
 * @param sem_op Semaphore operation (-1 for wait, 1 for signal).
 */
void sem_op(int semid, int sem_op)
{
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = sem_op;
    sb.sem_flg = 0;
    semop(semid, &sb, 1);
}

/**
 * Function to be executed by Process 1.
 * Generates random numbers and writes them to shared memory.
 * Forks Process 2 if the random number is 9.
 * Terminates if the random number is 0.
 *
 * @param shared_var Pointer to the shared memory variable.
 * @param semid Semaphore ID.
 */
void process1(int *shared_var, int semid)
{
    srand(time(0)); // Seed the random number generator
    while (1)
    {
        int randNum = rand() % 11;

        // Wait (P operation)
        sem_op(semid, -1);

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

        // Signal (V operation)
        sem_op(semid, 1);

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

    int semid = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    if (semid < 0)
    {
        perror("semget failed");
        exit(1);
    }

    // Initialize semaphore to 1
    semctl(semid, 0, SETVAL, 1);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // pass the shared memory variable to process1
        process1(shared_var, semid);
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
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}