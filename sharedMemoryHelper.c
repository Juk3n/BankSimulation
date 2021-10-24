#include "sharedMemoryHelper.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

static int getSharedBlock() {
    key_t key = ftok("zad1.c", 0);
    if(key == -1) printf("shared memory error\n");
    return shmget(key, sizeOfSharedMememorySegment, 0644 | IPC_CREAT);
}

int* attachMemoryBlock() {
    printf("Attached to existing SM\n");
    int sharedBlockId = getSharedBlock();
    return shmat(sharedBlockId, NULL, 0);
}

void detachMemoryBlock(int* dataPointer) {
    printf("Shared Memory disconnected!\n");
    shmdt(dataPointer);
}

void destroyMemoryBlock() {
    printf("Shared Memory removed!\n");
    int sharedBlockId = getSharedBlock();
    shmctl(sharedBlockId, IPC_RMID, NULL);
}