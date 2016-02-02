#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <assert.h>
#include <unistd.h>

/* main method of simple program that reads integers from a binary file and computes
 * the integer of theose integers.                                                              
 */
int main(int argc, char* argv[]){

  char *inputFile;
  int fd;
  struct stat buffer;
  int *arrayPointer;
  int status;
  int size;
  int n, i;
  int sum, average;

  //exit if there isn't exactly one command line argument                           
  if (argc != 2){
    fprintf(stderr, "usage: generate <file>\n");
    exit(1);
  }

  inputFile = argv[1];
  fd = open(inputFile, O_RDONLY);
  assert (fd > -1); //exit if open() failed                                         

  status = fstat(fd, &buffer);
  assert (status == 0); //exit if fstat() failed                                    

  size = buffer.st_size;  //size of the input file                                  
  arrayPointer = malloc(size/sizeof(int));//allocate space for size of the array    
  if (NULL == arrayPointer){
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }
  //iterate through binary file and add integers to the array                       
  i = 0;
  while ((n = read(fd, &arrayPointer[i], sizeof(int))) > 0){
    i++;
   }
  if (n  == -1){
    fprintf(stderr, "read failed\n");
    exit(1);
  }

  if (close(fd) == -1){
    fprintf(stderr, "closing file failed\n");
    exit(1);
  }
  //calculate sum and average                                                       
  sum = 0;
  for (i = 0; i < (size/sizeof(int)); i++){
    sum += arrayPointer[i];
  }
  average = sum/(size/sizeof(int));
  printf("Average = %d\n", average);
  return 0;
}

