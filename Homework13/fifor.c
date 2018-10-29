#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main () {
	int result;
	int fd;
	int multiplier;
	int multiplicand;
	int product;
	result = mkfifo("fifo.pipe",0600);
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
	write(fd, &product, sizeof(product));
	return 0;
};
