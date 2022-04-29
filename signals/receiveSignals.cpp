
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define true 1
#define false 0
#define MAXBUFFER 5
#define NULL ((void *)0)

pid_t pid;
bool keepRunning = 1;
int descritoresPipe[2];
char buffer[MAXBUFFER];
int comandoParaExecutar = 0;

static void lidar_SIGUSR1(int signo){ // função criada para lidar com o SIGUSR1
  printf("Received signal 10!\n");
}

static void lidar_SIGUSR2(int signo) {
  printf("Received signal 12!\n");
}

static void lidar_SIGTERM(int signo) {
  printf("Finishing process...\n");

  keepRunning = 0;
}

int main(void) {
  printf("My PID is %d.\n", getpid());

  while(keepRunning == 1) {
    if (signal(SIGUSR1, lidar_SIGUSR1) == SIG_ERR) // signal 10
      fprintf(stderr, "can't catch SIGUSR1.\n");
    if (signal(SIGUSR2, lidar_SIGUSR2) == SIG_ERR) // signal 12
      fprintf(stderr, "can't catch SIGUSR2.\n");
    if (signal(SIGTERM, lidar_SIGTERM) == SIG_ERR) // signal 15
      fprintf(stderr, "can't catch SIGTERM.\n");
  }
  return 0;
}