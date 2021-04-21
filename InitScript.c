#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int sem_set_id = semget(250, 1, IPC_CREAT | 0644);
    if (sem_set_id == -1) {
        printf("Cannot create semaphore\n");
    }
    printf("semsetid: %i\n", sem_set_id);

    int rc = semctl(sem_set_id, 0, SETVAL, 1);
    if (rc == -1) {
        printf("Cannot set value to semaphore\n");
    }

    int id = fork();
    switch(id) {
    case -1:
		printf("Error with fork");
		return 1;
		break;
	case 0: // child
        execl("./zad1", "./zad1", "2", "20", NULL);
	    break;
	default: // parent
        execl("./zad1", "./zad1", "1", "2", "100", "5", NULL);
        wait(NULL);
		break;
	}
}
