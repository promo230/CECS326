#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
/* File: pagetables.c */
/*
 Implement page tables.
 To make this simple, we have a page side of 1 integer (4 bytes).
*/
void* userprogram(void *);
int a1[3] = {0,3,6};
int a2[3] = {1,4,7};
int a3[3] = {2,5,8};
int pagetable[9];
int main () {
  pthread_t th;
  pthread_attr_t ta;
  if (pthread_attr_init(&ta)<0)
  {
    return -1;
  }
  if (pthread_attr_setdetachstate(&ta,PTHREAD_CREATE_DETACHED)<0)
  {
    return -1;
  }
  /*
    Create 3 child threads, give each of them access to a
    different set of pages. The first child will be using
    pages 0,3,6; the second child will be using pages 1,3,7;
    and the third child will be using pages 2,4,8.
  */
  pthread_create(&th,&ta,userprogram,a1);
  pthread_create(&th,&ta,userprogram,a2);
  pthread_create(&th,&ta,userprogram,a3);
  /* Cheap wait until the child threads are done. */
  sleep(10);
}
/*
 The child prints a Fibbinocci series, you should see the
 numbers 2,3,5,8,13. This works with one child. But with three
 children it won't work until you add the page table stuff.
 Then you should see three copies of the series, all 3 children
 should print ther 2's, then all three should print their 3's
 and so forth.
 The sleep is inserted to help make sure that you don't have two
 children accidentally using the same memory, do not remove it.
*/

void* userprogram(void* pages)
{
  /*
    We really passed an array of integers so we convert from a
    void * to an int*. Now pagetable[0], pagetable[1], and 
    pagetable[3] will be the array we were passed.
  */

  int* pagetable = pages;
  int i;
  /* 
    This printf is a test.
    You should see, 0,3,6 or 1,3,7 or 2,4,8. This test makes
    sure that the page table is being recieved by the child correctly.
  */
  printf("pagetable is %d %d %d\n",pagetable[0],pagetable[1],pagetable[2]);
  /*
    ONLY MODIFY FROM HERE DOWN.
    DO NOT CHANGE THE PROGRAM OR ADD ANY LINES.
    CHANGE THE MEMORY ACCESSES TO USE THE PAGE TABLE.
  */
  pagetable[1] = 1;
  pagetable[2] = 1;
  for (i = 0 ; i < 5 ; i++)
  {
    pagetable[0] = pagetable[1] + pagetable[2];
    pagetable[1] = pagetable[2];
    pagetable[2] = pagetable[0];
    sleep(1);
    printf("%d\n", pagetable[0]);
  };
};
