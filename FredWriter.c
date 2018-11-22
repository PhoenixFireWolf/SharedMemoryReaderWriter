#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void INThandler(int);
int shmid;
int id;
 
void INThandler (int sig){
	printf("\n%d Goodbye! thanks for sharing.\n", id);
	printf("%d cleaning up segid %d\n", id, shmid);
	shmctl(shmid, IPC_RMID, NULL);
	exit(0);
}

void USR1handler (int sig){
	printf("\n%d SIGUSR1 handler caught something.\n", id);
	shmctl(shmid, IPC_RMID, NULL);
	exit(0);
}

int main (void) {	

	key_t key;

	signal(SIGINT, INThandler);
	signal(SIGUSR1, USR1handler);

	key = ftok("/home/fkaup/somefile3", 'R');
	shmid = shmget(key, 1024, IPC_CREAT | 0644);

	char *data;
        char file[100];

	data = shmat(shmid, (void *)0, 0);
	if(data == (char *)(-1))
		perror("shmat");

	id = getpid();	

	while(1){
		printf("%d shmwriter: Enter something to save to shared memory: ", id);
		fgets(file, 100, stdin);
                strcpy(data, file);
	}

	return 0;
}
