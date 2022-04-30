#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


int main() { 
	int pid;
	int sinal;

	printf("PID a ser enviado o sinal: \n");
	scanf("%d", &pid);

	if ((getpgid(pid) < 0))	{
		printf("Processo não encontrado!\n");
		return 1;
	}

	printf("Número do sinal a ser enviado: \n");
	scanf("%d", &sinal);

	kill(pid, sinal);

	return 0;
}