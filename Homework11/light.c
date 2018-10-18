#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
#include <sys/wait.h> /* Needed for wait */
#include <sys/types.h> /* Needed for semaphore */
#include <sys/ipc.h> /* Needed for semaphore */
#include <sys/sem.h> /* Needed for semaphore */
#include <stdio.h>

//light.c
int main(int argc, char *argv[]){
        key_t myKey;
        int semid;
        myKey = ftok("heavy.c", 'x');
        //Declare structs for locking and unlocking
        static struct sembuf Wait = {0, -2, SEM_UNDO};
        static struct sembuf Signal = {0, 2, SEM_UNDO};
	//Check if semaphore exists and set value
	if((semid = semget(myKey, 1, IPC_CREAT | IPC_EXCL | 0600)) != -1){ 
        	semctl(semid, 0, SETVAL, 5);
	}else{
		semid = semget(myKey, 1, 0600);
	}

	printf("Semaphore ID %d\n", semid);
	int j = 0;
        for(j =0; j < 5; j++){
                //Lock
		semop(semid, &Wait, 1);

                printf("LightWeight Starting\n");
		fflush(stdout);
                sleep(2);
                printf("LightWeight Ending\n");
		fflush(stdout);

                //Release lock
		semop(semid, &Signal, 1);
		sleep(4);
        }//End for
	//Cleanup
	semctl(semid, 0, IPC_RMID, 0);
return 0;
};

