#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define true 1
#define false 0
#define MAXBUFFER 22
#define NULL ((void *)0)

pid_t pid;
int pipeTunnel[2];

char *checkPrime(char* numero) {
  int i=0;        
  int n = atoi(numero);
  if (n == 1) {
    return "é primo\n";
  }
  for (i=2;i<=n/2;i++) {
    if(n%i==0) {
      return "não é primo\n";
    }
  }
  return "é primo\n";
}

int main(void) {
  printf("My PID is %d.\n", getpid());

  int iterations;
  scanf("%d", &iterations);

  pipe(pipeTunnel);

  pid = fork();

  
  if (pid == 0) { //sou o filho
    char messageBuffer[MAXBUFFER];

    close(pipeTunnel[1]); // fecha o lado do pai

    read(pipeTunnel[0], messageBuffer, MAXBUFFER);

    while (atoi(messageBuffer) != 0) {
      printf("String recebida: '%s' %s", messageBuffer, checkPrime(messageBuffer));

      read(pipeTunnel[0], messageBuffer, MAXBUFFER);
    }

    exit(0);
  } else if (pid > 0) {// sou o pai

    close(pipeTunnel[0]); // fecha o lado do filho

    int value = 1;
    char messageBuffer[MAXBUFFER];

    while(iterations > 0) {
      sprintf(messageBuffer, "%d", value);
      write(pipeTunnel[1], messageBuffer, MAXBUFFER);

      printf("String enviada: '%s' \n", messageBuffer);

      value = value + (rand() % 99) + 1;

      iterations--;
    }
    sprintf(messageBuffer, "%d", 0);
    write(pipeTunnel[1], messageBuffer, MAXBUFFER);

    exit(0);
  }

  return 0;
}
