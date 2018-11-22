#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void INThandler(int);
int shmid;
char *data;
int id;

void INThandler (int sig){
	printf("\n%d shared contents: %s", id, data);
	shmdt(data);
	exit(0);
}

int main (void) {

	key_t key;

	signal(SIGINT, INThandler);

	key = ftok("/home/fkaup/somefile3", 'R');
	shmid = shmget(key, 1024, 0644 | IPC_CREAT);
	
	data = shmat(shmid, (void *)0, 0);

	id = getpid();	

	while(1){
		printf("%d shared contents: %s", id, data);
		sleep(10);

		if(atoi(data) == id){
			printf("%d shared contents: %s", id, data);
			printf("I have seen my PID, and have been instructed to exit. Goodbye!\n");			
			exit(0);
		}
	}

	return 0;
}
