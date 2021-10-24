#include "sharedMemoryHelper.h"
#include "semaphoreHelper.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

void readBankBalance(int *accounts, int accountNumber) {
    printf("Bank Balance (account %i) : %i\n", accountNumber, accounts[accountNumber]);
}

void changeBankBalance(int *accounts, int accountNumber, int amountOfMoney) {
    printf("....Changig Bank Balance....\n");
    accounts[accountNumber] += amountOfMoney;
}

void transferMoneyFromTo(int *accounts, int accountFrom, int accountTo, int amountOfMoney) {
    printf("....Transfering Money....\n");
    accounts[accountFrom] -= amountOfMoney;
    accounts[accountTo] += amountOfMoney;
}

int main(int argc, char *argv[]) {
    int *accounts;
    argc = argc - 1;

    int iterations = 0;
    if(argc == 2) iterations = atoi(argv[2]);
    if(argc == 3) iterations = atoi(argv[3]);
    if(argc == 4) iterations = atoi(argv[4]);

    accounts = attachMemoryBlock();
    for(int i = 0; i < iterations; i++) {
        semaphoreOpen();
        if(argc == 2) {
            readBankBalance(accounts, atoi(argv[1]));
        }
        else if(argc == 3) {
            printf("[Before transaction] "); readBankBalance(accounts, atoi(argv[1]));
            changeBankBalance(accounts, atoi(argv[1]), atoi(argv[2]));
            printf("[After transaction] "); readBankBalance(accounts, atoi(argv[1]));
            printf("\n");
        }
        else if(argc == 4) {
            sleep(1);
            printf("[Before transaction] "); readBankBalance(accounts, atoi(argv[1]));
            transferMoneyFromTo(accounts, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
            printf("[After transaction] "); readBankBalance(accounts, atoi(argv[1]));
            printf("\n");
        }
        else {
            printError("Bad number of arguments!");
        }
        semaphoreClose();
        sleep(1);
    }
    detachMemoryBlock(accounts);
}