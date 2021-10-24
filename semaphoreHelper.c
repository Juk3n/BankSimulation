#include "semaphoreHelper.h"
#include "error.h"

#include <sys/sem.h>
#include <stdio.h>

void semaphoreInit() {
    int semaphoreSetId = semget(250, 1, IPC_CREAT | 0644);
    if (semaphoreSetId == -1) {
        printError("Cannot create semaphore\n");
    }
    printf("Created semaphore\n");

    int rc = semctl(semaphoreSetId, 0, SETVAL, 1);
    if (rc == -1) {
        printError("Cannot set value to semaphore\n");
    }
}

void semaphoreOpen() {
    semaphoreSetId = semget(250, 1, IPC_CREAT | 0644);
    semaphoreBuffer.sem_num = 0;
    semaphoreBuffer.sem_op = -1;
    semaphoreBuffer.sem_flg = 0;
    semop(semaphoreSetId, &semaphoreBuffer, 1);
}

void semaphoreClose() {
    semaphoreBuffer.sem_num = 0;
    semaphoreBuffer.sem_op = 1;
    semaphoreBuffer.sem_flg = 0;
    semop(semaphoreSetId, &semaphoreBuffer, 1);
}