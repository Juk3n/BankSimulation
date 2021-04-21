int* getSharedBlock();
int* attachMemoryBlock(int sharedBlockId);
int detachMemoryBlock(int* sharedBlockId);
int destroyMemoryBlock(int sharedBlockId);