all: zad1 InitScript
zad1: zad1.c
	gcc zad1.c sharedMemoryHelper.c semaphoreHelper.c error.c -o zad1 -Wall

InitScript: InitScript.c
	gcc InitScript.c sharedMemoryHelper.c semaphoreHelper.c error.c -o InitScript -Wall

zip:
	zip pw.zip zad1.c InitScript.c sharedMemoryHelper.c semaphoreHelper.c error.c sharedMemoryHelper.h semaphoreHelper.h error.h Makefile pw4.txt