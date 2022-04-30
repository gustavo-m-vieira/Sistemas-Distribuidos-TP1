#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

bool finished = false;
int busyWaiting;

void sigintHandler(int sigNumber) {
    printf("SIGINT? Pra mim não serve de nada rs \n");
}

void sigquitHandler(int sigNumber) {
    printf("SIGQUIT? Pra mim não serve de nada rs \n");
}

void sigTerm(int sigNumber) {
    printf("SIGTERM? Agora sim vou finalizar esse programa rs \n");

    finished = 1;
}

int main() {
    printf("Busy wait (Se sim, digite 1)? ");
	scanf("%d", &busyWaiting);


    signal(SIGINT, sigintHandler);
    signal(SIGTERM, sigTerm);
    signal(SIGQUIT, sigquitHandler); 

    printf("My PID is %d.\n", getpid());

    while(!finished) {
        if (busyWaiting == 0) {
            pause();
        }
    }
    
    return 0;
}