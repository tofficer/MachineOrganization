
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <assert.h>
#include <unistd.h>

typedef struct node{
  int val;
  struct node *next;
} Node;

Node * createlist(int fd);
Node * listadd(Node *head, int intforlist);
void printlist(Node *head);
void playgame(Node * listhead);
int inlist(Node *head, int intvalue);

int main(int argc, char* argv[]){
  char *inputFile;
  int fd;
  Node *head;

  if (argc != 2){
    fprintf(stderr, "usage: generate <file>\n");
    exit(1);
  }

  inputFile = argv[1];
  fd = open(inputFile, O_RDONLY);
  assert (fd > -1);

  head = createlist(fd);

  if (close(fd) == -1){
    fprintf(stderr, "closing file failed\n");
    exit(1);
  }

  playgame(head);

  return 0;
}

Node * createlist(int fd){
  Node * head = NULL; //empty linked list                                                                       
  int n, buffer;

  while ((n = read(fd, &buffer, sizeof(int))) > 0){
    head = listadd(head, buffer);
  }
  if (n == -1){
    fprintf(stderr, "read failed\n");
    exit(1);
  }
  return head;
}

Node * listadd(Node *head, int intforlist){
  Node *temp;
  temp  = (Node*) malloc(sizeof(Node));
  if (NULL == temp){
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }
  temp->val = intforlist;
  temp->next = head;
  head = temp;

  return head;
  void printlist(Node *head){
  Node * current = head;

  while (current != NULL){
    printf("%d\n", current -> val);
    current = current->next;
  }
}
void playgame(Node * listhead){
  int str_to_int;
  char str[100];
  int n;

  printf("This game has you guess which integers are in the list.\n");
  printf("Enter an integer or q to quit.\n");

while((n = strncmp(fgets(str, 100, stdin), "q", 1)) != 0){
    str_to_int = atoi(str);
    if (inlist(listhead, str_to_int) == 1){
      printf("%d is in the list\n", str_to_int);
    }
    else {
      printf("%d is not in the list\n", str_to_int);
    }
  }
  printf("Quitting.\n");
}
int inlist(Node *head, int intvalue){
  Node * current = head;

  while (current != NULL){
    if (current->val == intvalue){
      return 1;
      break;
    }
    current = current->next;
  }
  return 0;
}
