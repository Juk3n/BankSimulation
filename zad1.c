#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void readBankBalance(int *accounts, int accountNumber) {
    printf("Bank Ballance (account %i) : %i\n", accountNumber, accounts[accountNumber]);
}

void increaseBankBalance(int *accounts, int accountNumber, int amountOfMoney) {
    accounts[accountNumber] += amountOfMoney;
}

void decreaseBankBalance(int *accounts, int accountNumber, int amountOfMoney) {
    accounts[accountNumber] -= amountOfMoney;
}

int main(int argc, char *argv[]) {
    int accounts[] = {0, 0, 0, 0, 0};

    int id = fork();
	switch(id) {
		case -1:
			printf("Error with fork");
			return 1;
			break;
		case 0: // child
            increaseBankBalance(accounts, 0, 100);
            readBankBalance(accounts, 0);
			break;
		default: // parent
            decreaseBankBalance(accounts, 0, 100);
            readBankBalance(accounts, 0);
			wait(NULL);
			break;
	}
}