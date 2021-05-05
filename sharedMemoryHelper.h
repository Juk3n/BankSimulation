#ifndef SEMAPHORE_HELPER_H
#define SEMAPHORE_HELPER_H

int* attachMemoryBlock();
void detachMemoryBlock(int* dataPointer);
void destroyMemoryBlock();

#endif