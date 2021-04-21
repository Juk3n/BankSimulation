#include <stdio.h>

void readAccountBalance(int *accountBalance) {
    printf("Account Ballance: %i\n", *accountBalance);
}

void increaseAccountBalance(int *accountBalance, int amountOfMoney) {
    *accountBalance += amountOfMoney;
}

void decreaseAccountBalance(int *accountBalance, int amountOfMoney) {
    *accountBalance -= amountOfMoney;
}

int main(int argc, char *argv[]) {
    int accountBalance = 0;
    readAccountBalance(&accountBalance);
    increaseAccountBalance(&accountBalance, 100);
    readAccountBalance(&accountBalance);
    decreaseAccountBalance(&accountBalance, 100);
    readAccountBalance(&accountBalance);
}