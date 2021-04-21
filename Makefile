all: zad1 InitScript
zad1: zad1.c
	gcc zad1.c sharedMemoryHelper.c -o zad1 -Wall

InitScript: InitScript.c
	gcc InitScript.c -o InitScript -Wall