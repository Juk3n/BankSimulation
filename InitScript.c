#include "semaphoreHelper.h"

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    semaphoreInit();

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
