#include "semaphoreHelper.h"
#include "sharedMemoryHelper.h"

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

void showBankAccount() {
	execl("./zad1", "./zad1", "2", "20", NULL);
}

void changeAccountValue() {
	execl("./zad1", "./zad1", "1", "100", "1", NULL);
}

void transerMoney() {
	execl("./zad1", "./zad1", "1", "2", "100", "1", NULL);
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("Program should have one argument!\n");
		return 0;
	}
	else if(atoi(argv[1]) <= 0) {
		printf("Zero threads!\n");
		return 0;
	}

	semaphoreInit();

	int numOfThreads = atoi(argv[1]) - 1;
	int id = 1;
	for(int i = 0; i < numOfThreads; i++) {
		if(id != 0) id = fork();
	}

    switch(id) {
    case -1:
		printf("Error with fork");
		return 1;
		break;
	case 0: // child
		//changeAccountValue();
        transerMoney();
	    break;
	default: // parent
		id = fork(); // additional thread created to clean stuff
		if (id == 0) showBankAccount();
		break;
	}

	wait(NULL);
	destroyMemoryBlock();
	return 0;
}
