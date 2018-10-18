#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
#include <sys/wait.h> /* Needed for wait */
#include <sys/types.h> /* Needed for semaphore */
#include <sys/ipc.h> /* Needed for semaphore */
#include <sys/sem.h> /* Needed for semaphore */
#include <stdio.h>
int main(int argc, char *argv[]){
//      semctl(semid, 0, SETVAL, 1);

        //Declare structs for locking and unlocking
        static struct sembuf Wait [3]= {{0,-1,SEM_UNDO},{1,-1,SEM_UNDO},
	 {2, -1, SEM_UNDO}};
        static struct sembuf Signal[3] =  {{0,-1,SEM_UNDO},{1,-1,SEM_UNDO},
	 {2, -1, SEM_UNDO}};
	static struct sembuf OpList[3];

        key_t myKey;
        int semid;
        myKey = ftok("heavy.c", 'x');
        semid = semget(myKey, 3, IPC_CREAT | 0600);
	semctl(semid, 0, SETVAL, 0);       
	semctl(semid, 1, SETVAL, 0);       
	semctl(semid, 2, SETVAL, 0);       
 
	//Print sem id
        printf("Semaphore ID %d\n", semid);
		
	// 0:H1 1:H2 2:H3
	int j =0;
        for(j =0; j < 5; j++){
                //Lock required resources (0,1,2)
                OpList[0] = Wait[0];
		OpList[1] = Wait[1];
		OpList[2] = Wait[2];
//		semop(semid, OpList, 3);
		//Print to console start
                printf("HeavyWeight Starting\n");
		fflush(stdout);
		//Sleep 4
                sleep(4);
		//Print to console end
                printf("HeavyWeight Ending\n");
		fflush(stdout);
                //Unlock required resources (1,2,3)
                OpList[0] = Signal[0];
		OpList[1] = Signal[1];
		OpList[2] = Signal[2];
//		semop(semid, OpList, 3);
		//Sleep 8
		sleep(8);
        }//End for
return 0;
};

