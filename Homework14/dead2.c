/* file: deadlock2.c */
/* You must correct this program. */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
int main () {
  /* The 5 semaphores (for the forks) are numbered 0 throug 4.
     The philosophers are also numbered 0 through 4. The fork
     on your left fork matches your philosopher number; the one on
     your right is one more than you number (except for philsopher 4
     whose right fork is number 0)
   */
  struct sembuf Waits[5] ;
  struct sembuf Signals[5] ;
  int i;
  int eat_round;
  int pid; /* for knowing who the parent is */
  key_t mykey;
  int semid;
  int waitstatus;

  mykey = ftok("dead2.c",'a');
  /* request 5 semaphores for my programs only */
  if (mykey == -1) {
    printf("File for key did not exist\n");
    return 1;
  }
  semid = semget(mykey, 5, IPC_CREAT | 0600 );
  for (i = 0; i < 5 ; i++ ) {
    /* initialize the wait, signal and count for each semaphore */
    Waits[i].sem_op = -1;
    Signals[i].sem_op = 1;
    Waits[i].sem_num = i;
    Signals[i].sem_num = i;
    Waits[i].sem_flg = SEM_UNDO;
    Signals[i].sem_flg = SEM_UNDO;
    semctl(semid,  i, SETVAL,  1);
  }
  /* fork 5 philosophers, 5 children for i = 0, 1, 2, 3, 4 */
  /* The parent is not a philosopher, it just does the wait */
  for (i = 0; i < 5 ; i++ ) {
    pid = fork();
    /* rest of loop is child, parent continues
       arround the loop to do fork child */
    if ( 0 == pid ) {
      /* each child is a philosopher */
      printf("Philosopher %d starting\n", i);
      for ( eat_round = 0; eat_round < 4; eat_round++ ) {
        printf("Philosopher %d grabbing left fork\n", i);
        semop(semid, &Waits[i], 1);
        sleep(1);
        semop(semid, &Waits[(i+1) % 5], 1);
        printf("Philosopher %d grabbing right fork\n", i);
        sleep(1);
        printf("Philosopher %d eat, round %d\n", i, eat_round);
        sleep(1);
        printf("Philosopher %d surrendering forks\n", i);
        semop(semid, &Signals[i], 1);
        semop(semid, &Signals[(i+1) % 5], 1);
      }
      printf("Philosopher %d exiting\n", i);
      return 0;
    }
  }
  /* Only the parent gets here, it waits for all the children to finish */
  for (i = 0; i < 5 ; i++ ) {
    wait3(&waitstatus,0,NULL);
  }
  /* All the children have exited, the parent now removes the semaphore */
  semctl(semid, 0, IPC_RMID, 0);
  return 0;
}
