#include "semaphoreHelper.h"

#include <sys/sem.h>
#include <stdio.h>

void semaphoreInit() {
    int semaphoreSetId = semget(250, 1, IPC_CREAT | 0644);
    if (semaphoreSetId == -1) {
        printf("Cannot create semaphore\n");
    }
    printf("semsetid: %i\n", semaphoreSetId);

    int rc = semctl(semaphoreSetId, 0, SETVAL, 1);
    if (rc == -1) {
        printf("Cannot set value to semaphore\n");
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