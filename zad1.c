#include <stdio.h>
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

    //get shared block
    key_t key = ftok("zad1.c", 0);
    if(key == -1) printf("shared memory error\n");
    int sharedBlockId = shmget(key, 4096, 0644 | IPC_CREAT);


    int id = fork();
	switch(id) {
		case -1:
			printf("Error with fork");
			return 1;
			break;
		case 0: // child

            //attach memory block
            accounts = shmat(sharedBlockId, NULL, 0);

            increaseBankBalance(accounts, 0, 100);
            readBankBalance(accounts, 0);

            //detach memory block
            shmdt(accounts);

			break;
		default: // parent

            //attach memory block
            accounts = shmat(sharedBlockId, NULL, 0);

            decreaseBankBalance(accounts, 0, 100);
            readBankBalance(accounts, 0);

            //detach memory block
            shmdt(accounts);

			wait(NULL);

            //destroy memory block
            shmctl(sharedBlockId, IPC_RMID, NULL);

			break;
	}
}