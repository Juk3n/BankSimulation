#ifndef SHARED_MEMORY_HELPER_H
#define SHARED_MEMORY_HELPER_H

int* attachMemoryBlock();
void detachMemoryBlock(int* dataPointer);
void destroyMemoryBlock();

#endif