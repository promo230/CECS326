#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int main (int argc, char* argv[]) {
	//Source file
	int src_fd;
	//Destination file
	int dest_fd;
	//The buffer used to copy the file
	char filebuf[256];
	//Size variables
	ssize_t readSizeIn, readSizeOut; 

	//Open the source file
	src_fd = open(argv[1],O_RDONLY);

	//If the open above fails, print to the console to let user know
	if(src_fd<0)
	{
		printf("The source file could not be opened...\n");
		exit(-1);
	}	
	
	//Check if the destination file already exists
	if(access(argv[2], F_OK ) != -1) 
	{
		printf("The destination file already exists...\n");
		exit(-1);
	} else {
		//Open the destination file
		dest_fd = open(argv[2], O_CREAT|O_WRONLY, sizeof(filebuf));
	}

	//If the open above fails, print to the console to let user know
	if(dest_fd<0)
	{
		printf("The destination file could not be opened...\n");
		exit(-1);
	}

	//Copy the source file into the destination file
	while (( readSizeIn = read(src_fd, filebuf, sizeof(filebuf)-1)) > 0)
	{
		readSizeOut = write(dest_fd, filebuf, (ssize_t) readSizeIn);
		if(readSizeOut != readSizeIn)
		{
			printf("The copy process did not execute successfully...\n");
			exit(-1);
		}
	}

	//Close both files at the end of the program
	close(src_fd);
	close(dest_fd);


	//Compute md5 hash	
	execlp("md5sum", "md5sum", argv[1], argv[2],  NULL);		
	return 0;
}
