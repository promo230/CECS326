#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main () {
	int myqueue;
	int myqueueSND;
	key_t mykey;
	int status;
	int multiplicand;
	int multiplier;
	int product;

	struct Mybuf {
		long mtype;
		int mint;
	};

	struct Mybuf buf;
	struct Mybuf bufSND;
	mykey = ftok( "sndmes.c" , 'a' );

	myqueue = msgget(mykey, IPC_CREAT | 0600 );
	myqueueSND = msgget(mykey, IPC_CREAT | 0600);
	if ( -1 == myqueue) {
		printf("error in msgget");
		return 1;
	}

	/* no special instructions, no flags */
	for(int i = 0; i < 5; i++){
	status = msgrcv(myqueue, &buf, sizeof(buf), 0, 0);
	multiplicand = buf.mint;
	printf("%d", multiplicand);
	
	status = msgrcv(myqueue, &buf, sizeof(buf), 0, 0);
	multiplier = buf.mint;
	printf("%d", multiplier);

	if ( -1 == status) {
		printf("error in msgrcv");
		return 1;
	}
	
	product = multiplicand*multiplier;
	bufSND.mint = product;
	msgsnd(myqueueSND, &bufSND, sizeof(bufSND), 0);
}
}
