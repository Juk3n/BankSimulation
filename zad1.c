#include <stdio.h>

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
    readBankBalance(accounts, 0);
    increaseBankBalance(accounts, 0, 100);
    readBankBalance(accounts, 0);
    decreaseBankBalance(accounts, 1, 100);
    readBankBalance(accounts, 1);
}