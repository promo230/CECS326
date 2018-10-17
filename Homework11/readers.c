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
        myKey = ftok("heavy.c", 'x');
        //Request 1 semaphore
//      semid = semget(myKey, 5, IPC_CREAT | 0600);
//      int semctl(int semid, int semnum, int cmd, arg);        
        semctl(semid, 0, SETVAL, 1);
        //Print the semaphore ID

        //Declare structs for locking and unlocking
        static struct sembuf Wait [4]= {{0,-1,SEM_UNDO},{1,-1,SEM_UNDO}, {2, -1, SEM_UNDO}, {3, -1, SEM_UNDO}};
        static struct sembuf Signal [4] =  {{0,-1,SEM_UNDO},{1,-1,SEM_UNDO}, {2, -1, SEM_UNDO}, {3, 1, SEM_UNDO}};
	static struct sembuf OpList[4];
        semid = semget(myKey, 4, IPC_CREAT | 0600);
        
        printf("Semaphore ID %d\n", semid);
	int j = 0;
	int count = 0;
        for(j =0; j < 5; j++){
                //Lock
                OpList[0] = Wait[0];
		OpList[1] = Wait[1];
		OpList[2] = Wait[2];
		semop(semid, OpList, 3);


		//Counter lock
		OpList[3] = Wait [3];
		if(count == 0){
			//lock writer
			count++;
		}
		//relase count lock
		OpList [3] = Signal [3];
		//Release readers	
                OpList[0] = Signal[0];
		OpList[1] = Signal[1];
		OpList[2] = Signal[2];
		semop(semid, OpList, 3);
		//print read
                printf("Reading\n");
		fflush(stdout);
                sleep(2);
                printf("Done reading\n");
		fflush(stdout);
                //Lock counter
		OpList[3] = Wait [3];
		count--;
		if(count == 0){
			//unlock writer
			
		}
		//relase count lock
		OpList [3] = Signal [3];
		sleep(4);
        }//End for
return 0;
};

