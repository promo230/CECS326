#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
#include <sys/wait.h> /* Needed for wait */
#include <sys/types.h> /* Needed for semaphore */
#include <sys/ipc.h> /* Needed for semaphore */
#include <sys/sem.h> /* Needed for semaphore */
#include <stdio.h>
int main (int argc, char* argv[]) {
	static struct sembuf BlockReaders = {0,-1,SEM_UNDO};
	static struct sembuf SignalReaders = {0,1,SEM_UNDO};
	static struct sembuf BlockWriters = {1,-1,SEM_UNDO};
	static struct sembuf SignalWriters = {1,1,SEM_UNDO};
	static struct sembuf BlockCounter = {2,-1,SEM_UNDO};
	static struct sembuf SignalCounter = {2,1,SEM_UNDO};
	static struct sembuf DecrementCounter = {3,-1,SEM_UNDO};
	static struct sembuf IncrementCounter = {3,1,SEM_UNDO};

	key_t key = ftok("readers.c", 1);
	if (key < 0) {
		printf("Invalid semaphore path\n");
		return 1;
	}

	int sem_id;

	if ((sem_id = semget(key, 4, IPC_CREAT | IPC_EXCL | 0600)) != -1) {
		for (int i = 0; i < 3; i++) semctl(sem_id, i, SETVAL, 1);
		semctl(sem_id, 3, SETVAL, 0);
	} else sem_id = semget(key, 4, 0600);

	for (int i = 0; i < 5; i++) {
		semop(sem_id, &BlockReaders, 1); /* P(BlockReaders) */
		semop(sem_id, &BlockCounter, 1); /* P(CounterLock) */
		int counter = semctl(sem_id, 3, GETVAL, 0); /* Counter */
		if (counter == 0) semop(sem_id, &BlockWriters, 1); /* P(WriterLock) */
		semop(sem_id, &IncrementCounter, 1); /* Counter++ */
		semop(sem_id, &SignalCounter, 1); /* V(CounterLock) */
		semop(sem_id, &SignalReaders, 1); /* V(BlockReaders) */
		printf("Reading\n");
		fflush(stdout);
		sleep(2);
		printf("Done reading\n");
		fflush(stdout);

		semop(sem_id, &BlockCounter, 1); /* P(CounterLock) */
		semop(sem_id, &DecrementCounter, 1); /* Counter-- */
		counter = semctl(sem_id, 3, GETVAL, 0); /* Counter */
		if (counter == 0) semop(sem_id, &SignalWriters, 1); /* V(WriterLock) */
		semop(sem_id, &SignalCounter, 1); /* V(CounterLock) */
		sleep(4);
	}
  
	semctl(sem_id, 0, IPC_RMID, 0);
};
