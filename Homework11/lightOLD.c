#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
#include <sys/wait.h> /* Needed for wait */
#include <sys/types.h> /* Needed for semaphore */
#include <sys/ipc.h> /* Needed for semaphore */
#include <sys/sem.h> /* Needed for semaphore */
#include <stdio.h>
int main(int argc, char *argv[]){
        //Declare structs for locking and unlocking
        static struct sembuf Wait[2] = {{0,-1,SEM_UNDO},{1, -1, SEM_UNDO}};
        static struct sembuf Signal[2] = {{0,1,SEM_UNDO},{1, 1, SEM_UNDO}};
	static struct sembuf OpList[2];

        key_t myKey;
        int semid;
        myKey = ftok("light.c", 'x');        
	semid = semget(myKey, 2, IPC_CREAT | 0600);
	semctl(semid, 0, SETVAL, 0);
	semctl(semid, 1, SETVAL, 0);

        //Print sem id
        printf("Semaphore ID %d\n", semid);
        
	// 0:L1 1:L2
	int j =0;
        for(j =0; j < 5; j++){//Begin for
                //Lock required resources (0,1)
		OpList[0] = Wait[0];
		OpList[1] = Wait[1];
//              semop(semid, OpList, 2);
		//Print to console start
                printf("LightWeight Starting\n");
		fflush(stdout);	
		//Sleep 4
                sleep(4);
		//Print to console end
                printf("LightWeight Ending\n");
		fflush(stdout);
		
                //Unlock required resources (3,4)
		OpList[0] = Signal[0];
		OpList[1] = Signal[1];
//              semop(semid, OpList, 2);
		
		//Sleep 8
		sleep(8);
        }//End for
return 0;
};

