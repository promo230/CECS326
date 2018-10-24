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
  struct sembuf Wait[5]  = { {0,-1,SEM_UNDO}, {1,-1,SEM_UNDO}, {2,-1,SEM_UNDO}, {3,-1,SEM_UNDO}, {4,-1,SEM_UNDO} };
  struct sembuf Signal[5] = { {0,1,SEM_UNDO}, {1,1,SEM_UNDO}, {2,1,SEM_UNDO}, {3,1,SEM_UNDO}, {4,1,SEM_UNDO} };
  int ch, i, pid;
  key_t mykey;
  int semid;
  union wait waitstatus;
  struct sembuf OpList[2];

  mykey = ftok("philosophers.c",'a');
  semid = semget(mykey, 5, IPC_CREAT | 0600 );
  //Initialize the semaphores
  semctl(semid,0,SETVAL,1);
  semctl(semid,1,SETVAL,1);
  semctl(semid,2,SETVAL,1);
  semctl(semid,3,SETVAL,1);
  semctl(semid,4,SETVAL,1);


  for (i = 0 ; i < 5 ; i++ )
  {
    pid = fork();
    if (pid == 0) break;
  }

  /*
  if (fork()==0) { 
    OpList[0] = Wait[0];
    OpList[1] = Wait[1];
    printf("Waiting\n");
    semop(semid,OpList,2);
    printf("Unlocked\n");
  } else { 
    sleep(3);
    OpList[0] = Signal[0];
    OpList[1] = Signal[1];
    semop(semid,OpList,2);
    wait3(&ch,0,NULL);
  }*/

  if (pid == 0)
  {
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
    semop(semid, &Wait[a],1);
    semop(semid, &Wait[b],1);
    printf("Philsopher %d eating...\n", pid);
    sleep(1);//Eat
    semop(semid, &Signal[a],1);
    semop(semid, &Signal[b],1);
    printf("Philsopher %d sleeping...\n", pid);
    sleep(4);//Sleeping
    }  
    return 0;
  }
  else
  {
    for (i = 0 ; i < 5 ; i++){
      wait3(&ch,0,NULL);
    }
    //Remove semaphore
    semctl(semid, 0, IPC_RMID, 0);
    semctl(semid, 1, IPC_RMID, 0);
    semctl(semid, 2, IPC_RMID, 0);
    semctl(semid, 3, IPC_RMID, 0);
    semctl(semid, 4, IPC_RMID, 0);
    return 0;
  }
}
