/* You need to switch from 2 to 5 semaphores.
   Initialize the 5 semaphores to unlocked.
   You still only need two semaphores in the OpList.
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
int main () {
  //Declare the sembufs
  struct sembuf Wait[5]  = { {0,-1,SEM_UNDO}, {1,-1,SEM_UNDO}, {2,-1,SEM_UNDO}, {3,-1,SEM_UNDO}, {4,-1,SEM_UNDO} };
  struct sembuf Signal[5] = { {0,1,SEM_UNDO}, {1,1,SEM_UNDO}, {2,1,SEM_UNDO}, {3,1,SEM_UNDO}, {4,1,SEM_UNDO} };
  //Declare variables
  int ch, i, pid;
  key_t mykey;
  int semid;
  union wait waitstatus;
  struct sembuf OpList[2];
   
  mykey = ftok("philosophers.c",'a');
  //Request semaphores
  semid = semget(mykey, 5, IPC_CREAT | 0600 );
  //Initialize the semaphores
  semctl(semid,0,SETVAL,1);
  semctl(semid,1,SETVAL,1);
  semctl(semid,2,SETVAL,1);
  semctl(semid,3,SETVAL,1);
  semctl(semid,4,SETVAL,1);

  //Fork 5 children process, when the pid is 0 (is a child) break out of the if loop, this guarantees 5 child processes are made
  for (i = 0 ; i < 5 ; i++ )
  {
    pid = fork();
    if (pid == 0) break;
  }


  if (pid == 0)
  {//The below logic is to account for the "circle" of philosophers. When it gets to the "end" of one circle, the below logic resets i to the first philosopher and i + 1 to the philsopher next to i.
    int a, b;
    pid = getpid();
    for(int i =0; i < 5; i++){
      if((i+1) > 4){
        a = 0;
      }else{
        a = i+1;
       }
        b = i;
      if (i == 4){
        b = a;
        a = i;
       }
    //Lock resources whie eating
    semop(semid, &Wait[a],1);
    semop(semid, &Wait[b],1);
    //Display eating and pid
    printf("Philsopher %d eating...\n", pid);
    sleep(1);//Eat
    //Unlock resources and sleep
    semop(semid, &Signal[a],1);
    semop(semid, &Signal[b],1);
    //Display sleeping and pid
    printf("Philsopher %d sleeping...\n", pid);
    sleep(4);//Sleeping
    }  
    return 0;
  }
  else
  {
    //For all 5 child processes, force the parent to wait for the child process to finish
    for (i = 0 ; i < 5 ; i++){
      wait3(&ch,0,NULL);
    }
    //Remove all the semaphores - cleanup
    semctl(semid, 0, IPC_RMID, 0);
    semctl(semid, 1, IPC_RMID, 0);
    semctl(semid, 2, IPC_RMID, 0);
    semctl(semid, 3, IPC_RMID, 0);
    semctl(semid, 4, IPC_RMID, 0);
    return 0;
  }
}
