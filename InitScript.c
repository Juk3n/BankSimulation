#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int id = fork();
    switch(id) {
    case -1:
		printf("Error with fork");
		return 1;
		break;
	case 0: // child
        execl("./zad1", "./zad1", "1", "3", "-4", NULL);
	    break;
	default: // parent
        execl("./zad1", "./zad1", "1", "20", NULL);
	    wait(NULL);
		break;
	}
}
