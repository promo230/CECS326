#include <stdlib.h> /* Needed for fork */
#include <stdio.h> /* Needed for printf. */
#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
#include <sys/wait.h> /*Needed for no error on wait3. */
int sum;
int main (int argc, char* argv[]) {
  int i;
  int isChild;
  sum = 0;
  isChild = fork();  /* create a new process */

  for (i=1; i<=10; i++) {
    sum += i;
    //Check if process is a child
    if(isChild == 0){
      printf("sum is C%d\n", sum);
      sleep(2);
    }
    //If process is not a child, it is a parent 
    else
    {
      printf("sum is P%d\n", sum);
      sleep(1);
    }
    fflush(stdout);
  }

  //Logic for "If there is an argument (other than file name) and you are parent, wait for child
  if(argv[1] || isChild != 0){
    int child;
    wait3(&child, 0, NULL);
    return 0 + child;
  }

  //Logic for "If there is no argument (or you are the child), execute return immediately
  if(argc == 0 || isChild == 0 ){
    return 0;
  }
  return 0;
};
