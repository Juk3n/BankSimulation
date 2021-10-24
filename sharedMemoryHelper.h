#ifndef SHARED_MEMORY_HELPER_H
#define SHARED_MEMORY_HELPER_H

int sizeOfSharedMememorySegment = 4096;

int* attachMemoryBlock();
void detachMemoryBlock(int* dataPointer);
void destroyMemoryBlock();

#endif