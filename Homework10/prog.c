#include <stdlib.h> /* Needed for fork */
#include <stdio.h> /* Needed for printf. */
#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
#include <sys/wait.h> /* Needed for wait */
#include <sys/types.h> /* Needed for semaphore */
#include <sys/ipc.h> /* Needed for semaphore */
#include <sys/sem.h> /* Needed for semaphore */

int main(int argc, char *argv[]){
	//Create and initialize a semaphore before fork
	key_t myKey;
	int semid;
	myKey = ftok("prog.c", 'x');
	//Request 1 semaphore
	semid = semget(myKey, 1, IPC_CREAT | 0600);
//	int semctl(int semid, int semnum, int cmd, arg);	
	semctl(semid, 0, SETVAL, 1);
	//Print the semaphore ID
	printf("Semaphore ID %d\n", semid);

	//Declare structs for locking and unlocking the intersection(semaphore)
	static struct sembuf Wait = {0,-1,SEM_UNDO};
	static struct sembuf Signal = {0,1,SEM_UNDO};
	
	//Fork a process
	int isChild = fork();
	int j = 0;
	while(j<10){
		//Child logic	
		if(isChild == 0){
		//Lock intersection
		semop(semid, &Wait, 1); //Wait for car to cross
		printf("N/S car entering intersection\n");
		sleep(1);//Car crossing intersection time
		printf("N/S car leaving intersection\n");
		//Release lock
		semop(semid, &Signal, 1); //Signal car has crossed
		}//End if

		//Parent logic
		else{
		//Lock intersection
		semop(semid, &Wait, 1); //Wait for car to cross
		printf("E/W car entering intersection\n");
		sleep(1);//Car crossing intersection time
		printf("E/W car leaving intersection\n");
		//Release lock
		semop(semid, &Signal, 1);//Signal car has crossed
		}//End else
		j+=1; 
		//Testing
		//printf("J = %d\n", j);
	}//End for
return 0;
};
