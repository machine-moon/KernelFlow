#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_KEY 0x1234 // Fixed key for shared memory

int main()
{
    // shmget - creates or opens a shared memory segment, obtains its identifier
    int shmid = shmget(SHM_KEY, sizeof(int), 0666 | IPC_CREAT);

    /*
     * shmat 3 params are shmid, shmaddr, shmflg
     * shmid is the shared memory id returned by shmget
     * shmaddr is the address at which to attach the shared memory segment. NULL lets the system choose the address.
     * shmflg is the flags. 0 means no special flags are set. By default, the process will have read and write access to the shared memory segment if it was created with read and write permissions.
     */
    int *shared_var = (int *)shmat(shmid, NULL, 0);

    while (*shared_var != 0) // Loop until shared_var is 0 (random number generated)
    {
        printf("I am Process 2, Shared Random Number: %d\n", *shared_var);
        sleep(1);
    }

    // shmdt - detaches the shared memory segment from the calling process
    shmdt(shared_var);
    return 0;
}