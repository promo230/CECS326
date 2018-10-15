#include <stdlib.h> /* Needed for fork */
#include <stdio.h> /* Needed for printf. */
#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
//#include <sys/wait.h> /*Needed for no error on wait3. */
#include <pthread.h> /*Needed for thread.*/

int i;
char letters[26];
int ch, n = 0;

void* ChildThread(void *arg){
 for (i=0; i<=10; i++) {
      printf("C %c\n", letters[i]);
      sleep(2);    
  }
}

int main (int argc, char *argv[]) {
  //Sleep for 5 seconds
  printf("Sleeping...\n");
  sleep(5);
  while((ch = getchar()) != '\n' && n <26){
    letters[n] = ch;
    ++n;
  }
   
  pthread_t th;
  pthread_attr_t ta;
   
 (void) pthread_attr_init(&ta);
 (void) pthread_attr_setdetachstate(&ta, PTHREAD_CREATE_DETACHED);
  pthread_create(&th, &ta, (void * (*)(void *))ChildThread, NULL);
    for(i=0; i<=10; i++)
    {
      printf("P %c\n", letters[i]);
      sleep(1);
    }
 return 0;
};
