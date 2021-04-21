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

void changeBankBalance(int *accounts, int accountNumber, int amountOfMoney) {
    accounts[accountNumber] += amountOfMoney;
}

int main(int argc, char *argv[]) {
    int *accounts;

    argc = argc - 1;
    switch(argc) {
    case 2: // read account
        accounts = attachMemoryBlock();

        for(int i = 0; i < atoi(argv[2]); i++) {
            readBankBalance(accounts, atoi(argv[1]));
        }

        detachMemoryBlock(accounts);
        break;

    case 3: // increase/decrease bank account
        accounts = attachMemoryBlock();

        for(int i = 0; i < atoi(argv[2]); i++) {
            changeBankBalance(accounts, atoi(argv[1]), atoi(argv[3]));
        }

        detachMemoryBlock(accounts);
        break;
    case 4:
        break;
    default:
        printf("Bad number of arguments!");
        break;
    }
}