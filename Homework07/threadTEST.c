#include <stdlib.h> /* Needed for fork */
#include <stdio.h> /* Needed for printf. */
#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
#include <sys/wait.h> /* Needed for wait */
#include <pthread.h>
int i;
int sum;
void* ChildThread(void* ptr) {
  for (i=1; i<=10; i++) {
    sum += i;
    int myChar = getchar();
    printf("%c sum is %d: %c\n", 'C', sum, myChar);
    sleep(2);
    fflush(stdout);
  }
 
}

int main (int argc, char* argv[]) {
  int is_child;
  sum = 0;

  printf("%s", "Sleeping\n");
  fflush(stdout);

  sleep(4);

  pthread_t threadp;
  pthread_create(&threadp, NULL, &ChildThread, NULL);

  for (i=1; i<=10; i++) {
    sum += i;
    int myChar = getchar();
    printf("%c sum is %d: %c\n", 'P', sum, myChar); 
    sleep(1);
    fflush(stdout);
  }
};
