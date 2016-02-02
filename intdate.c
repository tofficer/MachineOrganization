#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int count = 0;
int seconds = 3;

//handler for SIGINT                                                                
void int_handler(int signum){
  count++;
  if (count >= 5){
    printf("\nFinal Control-c caught. Exiting.\n");
    exit(0);
  }
  printf("\nControl-c caught. %d more before program is ended.\n", 5-count);
}

//handler for SIGALRM                                                               
void alarm_handler(int signum){
  time_t rawtime;
  time(&rawtime);
  printf("Current time is %s", ctime(&rawtime));
  if (alarm(seconds) != 0){
    perror("Error detected with alarm\n");
    exit(1);
  }
  alarm(seconds);
}

int main(){
  printf("Date will be printed every 3 seconds.\n");
  printf("Enter ^C 5 times to end the program:\n");

  //setup sigaction structs                                                         
  struct sigaction aact;
  memset(&aact, 0, sizeof(aact));
  aact.sa_handler = alarm_handler;
  
  struct sigaction iact;
  memset(&iact, 0, sizeof(iact));
  iact.sa_handler = int_handler;

  if (sigaction(SIGALRM, &aact, NULL) == -1){
      perror("Failed to install the alarm handler\n");
      exit(1);
  }
  sigaction(SIGALRM, &aact, NULL);

  if (sigaction(SIGINT, &iact, NULL) == -1){
    perror("Failed to install the int handler\n");
    exit(1);
  }
  sigaction(SIGINT, &iact, NULL);

  if (alarm(seconds) != 0){
    perror("Error detected with alarm\n");
    exit(1);
  }
  alarm(seconds);

  while(1){
  }
  exit(0);
}
