#include "sharedMemoryHelper.h"

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
    if(argc == 2 || argc == 3) iterations = atoi(argv[2]);
    if(argc == 4) iterations = atoi(argv[4]);

    accounts = attachMemoryBlock();
    for(int i = 0; i < iterations; i++) {
        int sem_set_id = semget(250, 1, IPC_CREAT | 0644);
        struct sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = -1;
        sem_op.sem_flg = 0;
        semop(sem_set_id, &sem_op, 1);

        if(argc == 2) {
            readBankBalance(accounts, atoi(argv[1]));
        }
        else if(argc == 3) {
            printf("[Before transaction] "); readBankBalance(accounts, atoi(argv[1]));
            changeBankBalance(accounts, atoi(argv[1]), atoi(argv[3]));
            printf("[After transaction] "); readBankBalance(accounts, atoi(argv[1]));
            printf("\n");
        }
        else if(argc == 4) {
            printf("[Before transaction] "); readBankBalance(accounts, atoi(argv[1]));
            transferMoneyFromTo(accounts, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
            printf("[After transaction] "); readBankBalance(accounts, atoi(argv[1]));
            printf("\n");
        }
        else {
            printf("Bad number of arguments!");
        }

        sem_op.sem_num = 0;
        sem_op.sem_op = 1;
        sem_op.sem_flg = 0;
        semop(sem_set_id, &sem_op, 1);
    }
    detachMemoryBlock(accounts);
}