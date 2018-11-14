#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(int argc, char *argv[]){
	int fd;
	int pos;
	char newLetter;
	char *filePtr;
	struct stat st;
	stat(argv[1],&st);
	//Open file with read and write access
	fd = open(argv[1],O_RDWR);
	int size = st.st_size;
	//Map file
	filePtr = mmap(0,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	//Loop to ask user to change three indexes
	for(int i = 0;i<3;i++){

		printf("\nPosition to change (0 - %d): ",size-1);
		scanf("%d",&pos);
		if(pos<0 || pos>=size){
			printf("Choose a valid position...");
		}
		else{
			printf("\nNew letter for position %d : ", pos);
			scanf(" %c",&newLetter);
			filePtr[pos] = newLetter;
		}
	}
	//Unmapping
	munmap(filePtr,size);
	//Close file
	close(fd);
}
