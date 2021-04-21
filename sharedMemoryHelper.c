#include "sharedMemoryHelper.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int* getSharedBlock() {
    //get shared block
    key_t key = ftok("zad1.c", 0);
    if(key == -1) printf("shared memory error\n");
    return shmget(key, 4096, 0644 | IPC_CREAT);
}

int* attachMemoryBlock(int sharedBlockId) {
    return shmat(sharedBlockId, NULL, 0);
}

int detachMemoryBlock(int* dataPointer) {
    shmdt(dataPointer);
}

int destroyMemoryBlock(int sharedBlockId) {
    shmctl(sharedBlockId, IPC_RMID, NULL);
}