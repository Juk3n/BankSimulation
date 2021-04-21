all: zad1
zad1: zad1.c
	gcc zad1.c sharedMemoryHelper.c -o zad1 -Wall