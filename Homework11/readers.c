#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
#include <sys/wait.h> /* Needed for wait */
#include <sys/types.h> /* Needed for semaphore */
#include <sys/ipc.h> /* Needed for semaphore */
#include <sys/sem.h> /* Needed for semaphore */
#include <stdio.h>
int main(int argc, char *argv[]){
        //Create and initialize a semaphore before fork
        key_t myKey;
        int semid;
        myKey = ftok("light.c", 'x');
        //Request 1 semaphore
        semid = semget(myKey, 4, IPC_CREAT | 0600);
//      int semctl(int semid, int semnum, int cmd, arg);        
        semctl(semid, 0, SETVAL, 1);
        //Print the semaphore ID
        printf("Semaphore ID %d\n", semid);

        //Declare structs for locking and unlocking
        static struct sembuf Wait = {0,-1,SEM_UNDO};
        static struct sembuf Signal = {0,1,SEM_UNDO};

        
        int j = 0;
        for(j =0; j < 5; j++){
                //Lock
                semop(semid, &Wait, 1);
                printf("Reading \n");
                sleep(2);
                printf("Done reading\n");
                //Release lock
                semop(semid, &Signal, 1);
		sleep(4);
        }//End for
return 0;
};

