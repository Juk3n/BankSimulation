#include "sharedMemoryHelper.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void readBankBalance(int *accounts, int accountNumber) {
    printf("Bank Balance (account %i) : %i\n", accountNumber, accounts[accountNumber]);
}

void increaseBankBalance(int *accounts, int accountNumber, int amountOfMoney) {
    accounts[accountNumber] += amountOfMoney;
}

void decreaseBankBalance(int *accounts, int accountNumber, int amountOfMoney) {
    accounts[accountNumber] -= amountOfMoney;
}

int main(int argc, char *argv[]) {
    int *accounts;
    int* sharedBlockId = getSharedBlock();

    int id = fork();
    switch(id) {
		case -1:
			printf("Error with fork");
			return 1;
			break;
		case 0: // child
            accounts = attachMemoryBlock(sharedBlockId);

            increaseBankBalance(accounts, 0, 100);
            readBankBalance(accounts, 0);

            detachMemoryBlock(accounts);

			break;
		default: // parent
            accounts = attachMemoryBlock(sharedBlockId);

            decreaseBankBalance(accounts, 0, 100);
            readBankBalance(accounts, 0);

            detachMemoryBlock(accounts);

			wait(NULL);

            destroyMemoryBlock(sharedBlockId);
			break;
	}
}