#ifndef SEMAPHORE_HELPER_H
#define SEMAPHORE_HELPER_H

struct sembuf semaphoreBuffer;
int semaphoreSetId;

void semaphoreInit();
void semaphoreOpen();
void semaphoreClose();

#endif