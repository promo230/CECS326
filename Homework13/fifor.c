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

	int multiplier;
	int multiplicand;
	int product;
	fd1 = open("fifo1.pipe", O_WRONLY);	
	fd = open("fifo.pipe",O_RDONLY);
	//Read multiplicand from pipe
	read(fd, &multiplicand, sizeof(multiplicand));
	//Read multiplier from pipe
	read(fd, &multiplier, sizeof(multiplier));
	//Multiply
	printf("Multiplicand is: %d\n", multiplicand);
	printf("Multiplier is %d\n", multiplier);
	product = multiplier*multiplicand;
	printf("Product is: %d\n", product);
	//Write answer to other pipe
	write(fd1, &product, sizeof(product));
	close(fd1);
	}
	return 0;
};
