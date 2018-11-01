#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main () {
	
	int fd;
	mkfifo("fifo.pipe",0600);
	int fd1;
	mkfifo("fifo1.pipe", 0600);	
	for(int i = 0; i < 5; i++){
	fd1 = open("fifo1.pipe", O_RDONLY);
	fd = open("fifo.pipe",O_WRONLY);
	int multiplicand;
	int multiplier;
	int product;	
	//cin the multiplicand
	printf("Multiplicand: ");
	scanf("%d", &multiplicand);
	//Write multiplicand to pipe
	write(fd, &multiplicand, sizeof(multiplicand));
	//cin the multiplier
	printf("Multiplier: ");
	scanf("%d", &multiplier);
	//Write multiplier to pipe
	write(fd, &multiplier, sizeof(multiplier));
	//Read back the answer from the other pipe
	read(fd1,&product,sizeof(product));
	//Display answer
	printf("Product is: %d\n\n", product);
	}
	return 0;
};
