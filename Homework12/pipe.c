#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int toParent[2], toChild[2];
  //Make pipes
  pipe(toParent); pipe(toChild);

  if (fork()==0) {
    for(int i =0; i<5; i++){
      close(toParent[0]); /* child */
      close(toChild[1]);
      //Variables
      int multiplicand;
      int multiplier;
      int quotient;
      //Read multiplicand from the pipe
      read(toChild[0], &multiplicand, sizeof(multiplicand));
      //Read multiplier from the pipe
      read(toChild[0], &multiplier, sizeof(multiplier));
      //Multiply
      quotient = multiplicand*multiplier;
      //Write the answer the other pipe
      write(toParent[1],&quotient,sizeof(quotient));
    }
  } else {
      for(int i = 0; i<5; i++){
      close(toChild[0]); /* parent */
      close(toParent[1]);
      //Variables
      int multiplicand;
      int multiplier; 
      int answer;
      //cin the multiplicand
      printf("Multiplicand: ");
      scanf("%d", &multiplicand);
      //Write the multiplicand to the pipe
      write(toChild[1], &multiplicand, sizeof(multiplicand));
      //cin the multiplier
      printf("Multiplier: ");
      scanf("%d", &multiplier);
      //Write the multiplier to the pipe
      write(toChild[1], &multiplier, sizeof(multiplier));
      //Read back the answer from the other pipe   
      read(toParent[0],&answer,sizeof(answer));
      //Display answer
      printf("Answer is: %d\n\n", answer);
    }
  }
  return 0;
}

