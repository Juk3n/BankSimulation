#include "sharedMemoryHelper.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

static int getSharedBlock() {
    key_t key = ftok("zad1.c", 0);
    if(key == -1) printf("shared memory error\n");
    return shmget(key, 4096, 0644 | IPC_CREAT);
}

int* attachMemoryBlock() {
    int sharedBlockId = getSharedBlock();
    return shmat(sharedBlockId, NULL, 0);
}

void detachMemoryBlock(int* dataPointer) {
    shmdt(dataPointer);
}

void destroyMemoryBlock() {
    int sharedBlockId = getSharedBlock();
    shmctl(sharedBlockId, IPC_RMID, NULL);
    printf("Shared Memory removed!\n");
}