#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 0x1234 // Fixed key for shared memory
#define SEM_KEY 0x5678 // Fixed key for semaphore

/**
 * Function to perform semaphore operations.
 *
 * @param semid Semaphore ID.
 * @param sem_op Semaphore operation
 */
void sem_op(int semid, int sem_op)
{
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = sem_op;
    sb.sem_flg = 0;
    semop(semid, &sb, 1);
}

int main()
{
    int shmid = shmget(SHM_KEY, sizeof(int), 0666 | IPC_CREAT);

    // shmid - Shared memory ID.
    // param2 NULL - Attach at any address.
    // param3 0 - Read/Write access.

    int *shared_var = (int *)shmat(shmid, NULL, 0);
    int semid = semget(SEM_KEY, 1, 0666 | IPC_CREAT);

    while (*shared_var != 0)
    {
        // Wait
        sem_op(semid, -1);

        printf("I am Process 2, Shared Random Number: %d\n", *shared_var);
        sleep(1);

        // Signal Process 1
        sem_op(semid, 1);
    }
    shmdt(shared_var);
    return 0;
}