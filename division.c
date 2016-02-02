#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int count = 0;

//handler for SIGINT                                                                
void int_handler(int signum){
  printf("There were %d successfully completed divisions\n", count);
  exit(0);
}

//handler for SIGFPE                                                                
void fpe_handler(int signum){
  printf("Divide by 0 error detected. There were %d successfully completed division\
s\n", count);
  exit(1);
}

int main(){
  //setup sigaction structs                                                         
  struct sigaction fpeact;
  memset(&fpeact, 0, sizeof(fpeact));
  fpeact.sa_handler = fpe_handler;

  struct sigaction intact;
  memset(&intact, 0, sizeof(intact));
  intact.sa_handler = int_handler;

  if (sigaction(SIGFPE, &fpeact, NULL) == -1){
    perror("Failed to install the fpe handler\n");
    exit(1);
  }
  sigaction(SIGFPE, &fpeact, NULL);
  
  if (sigaction(SIGINT, &intact, NULL) == -1){
    perror("Failed to install the int handler\n");
    exit(1);
  }
  sigaction(SIGINT, &intact, NULL);

  char str1[100];
  char str2[100];
  int num1, num2;
  int quotient, remainder;

  //infinite loop that continuously asks user for 2 numbers to use for division     
  while(1){
    printf("Enter first integer: ");
    fgets(str1, 100, stdin);
    num1 = atoi(str1);
    printf("Enter second integer: ");
    fgets(str2, 100, stdin);
    num2 = atoi(str2);
    quotient = num1/num2;
    remainder = num1%num2;
    printf("%d / %d is %d with a remainder of %d\n", num1, num2, quotient, remainder);
    count++;
  }

