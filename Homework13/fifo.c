#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main () {
	int result;
	int fd;
	int multiplicand;
	int multiplier;
	int product;
	result = mkfifo("fifo.pipe",0600);
	fd = open("fifo.pipe",O_WRONLY);
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
	read(fd,&product,sizeof(product));
	//Display answer
	printf("Product is: %d\n\n", product);
	return 0;
};
