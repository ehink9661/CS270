/* server.c
 *
 * CS 270-01.Bolden..........Ethan Hinkle
 * 26 November, 2021........hink9661@vandals.uidaho.edu
 *
 * This is the server c file for the assigment 4 creating a server client
 * system in C
 *--------------------------------------------------------------------
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void comm(int sock, char buf[]); // executes the clients request
void error(const char *msg);
int tokenize(char *s, char *cmd[]);
int calc(char *cmd[], int sock);
int isNumber(char *cmd[], int i);
int isOperator(char *cmd[]);

int main(int argc, char *argv[]){
  int sockfd, newsockfd, portno, pid, n;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  if(argc < 2){
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) error("ERROR opening socket");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");
  listen(sockfd,5);
  clilen = sizeof(cli_addr);
  while(1){
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if(newsockfd < 0) error("ERROR on accept");

    bzero(buffer,256); // reads before fork to allow for client side termination
    n = read(newsockfd, buffer, 255);
    if(n < 0) error("ERROR reading from socket");
    if(!(strcmp(buffer, "exit\n"))){ // if client gives exit\n command, terminates server
      printf("Exit Command\n");
      break; // should never be used, but here for the assignment and debugging
    }
    pid = fork();
    if(pid < 0) error("ERROR on fork");
    if(pid == 0){
      close(sockfd);
      comm(newsockfd, buffer);
      exit(0);
    }
    else close(newsockfd);
  }
  close(sockfd);
  exit(0); // terminates connection, return doesn't seem to do it properly
  return 0;
}

void error(const char *msg){ // prints error message, then terminates
    perror(msg);
    exit(1);
}

void comm(int sock, char buffer[]){ // handles communicaton and arithmatic of the server
  int n;
  int num = 0;
  int result;
  char *ops[256]; // stores operands
  printf("Here is the message: %s\n",buffer); // prints message on server
  num = tokenize(buffer, ops); // tokenize the input
  if(num != 3){ // should only have three tokens, otherwise invalid number of ops
    n = write(sock, "Invalid number of commands recieved\n", 36); // informs user of failure
    if (n < 0) error("ERROR writing to socket");
    error("ERROR recieved invalid number of commands"); // not 3 commands
  }
  if(isOperator(ops)){ // checks if operator is valid
    n = write(sock, "Invalid operator recieved\n", 26); // informs user of failure
    if (n < 0) error("ERROR writing to socket");
    error("ERROR invalid operation"); // operation only 1 char long, so [0][1] shoud be \0
  }
  if(isNumber(ops, 1)){ // checks if first operand is a number
    n = write(sock,"Operand 1 Invalid\n", 18); // informs user of failure
    if (n < 0) error("ERROR writing to socket");
    error("ERROR operand 1 invalid");
  }
  if(isNumber(ops, 2)){ // checks if second operand is a number
    n = write(sock,"Operand 2 Invalid\n", 18); // informs user of failure
    if (n < 0) error("ERROR writing to socket");
    error("ERROR operand 2 invalid");
  }
  result = calc(ops, sock); // calculate output
  snprintf(buffer, 256, "The result of the operation: %d\n", result);
  printf("The result: %d\n", result);
  n = write(sock, buffer, strlen(buffer));
  if(n < 0) error("ERROR writing to  socket");
}

int tokenize(char *s, char *cmd[]){ /* creates array of tokens for math */
  char *token;
  int j = 0;
  token = strtok(s, " "); /* get first token, up to space */
  if(token == NULL){ /* no commands entered, fixed edge case with ' ' and '\n' */
    return 0;
  }
  while (token != NULL){ /* check to see if there are any tokens left in s */
    cmd[j] = token;
    j++; /* increments cmd to store next command token */
    token = strtok(NULL, " "); /* get next token */
  }
  cmd[j] = NULL; /* ends array with NULL */
  return j; /* returns number of tokenized words */
}

int calc(char *cmd[], int sock){
  int d;
  char x = cmd[0][0]; /* get the operation */
  int y = strtol(cmd[1], NULL, 0);
  int z = strtol(cmd[2], NULL, 0);
  switch(x){
  case '+':
    d = y+z;
    break;
  case '-':
    d = y-z;
    break;
  case '*':
    d = y*z;
    break;
  case '/':
    d = y/z;
    break;
  case '%':
    d = y%z;
    break;
  default:
    error("ERROR with operation"); // if illegal operand got past first check, error
    break;
  }
  return d;
}

int isNumber(char *cmd[], int i){ // checks if the string is a number, i is string in array
  int j = 0;
  if(cmd[i][j] == '\0'){ // recieved empty string
    return -1;
  }
  while((cmd[i][j] != '\0') && (cmd[i][j] != '\n')){ // runs until \0 or \n
    if(cmd[i][j] == '-'){ // if negative, increment
      j++;
    }
    if((cmd[i][j] < 48) || (cmd[i][j] > 57)){ // char is outside number ascii value
      return 1; // return 1 on fail
    }
    j++;
  }
  return 0; // returned if string is number
}

int isOperator(char *cmd[]){
  int j;
  char ops[5] = {'+', '-', '*', '/', '%'}; // array of viable operations
  if(cmd[0][1] != '\0'){ // as all ops are only a char, 0 1 must be \0
    return 1; // failure
  }
  for(j = 0; j < 5; j++){ // runs throuhg all ops, comparing until match or end of loop
    if(cmd[0][0] == ops[j]){
      return 0; // succcess
    }
  }
  return 1; // failure
}
