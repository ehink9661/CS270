/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int dostuff(int); /* function prototype */
void error(const char *msg);
int tokenize(char *s, char *cmd[]);
double calc(char *cmd[]);
int isNumber(char *cmd[], int i);

int main(int argc, char *argv[]){
  int sockfd, newsockfd, portno, pid;
  int x = 3;
  socklen_t clilen;
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
  while(x--){
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if(newsockfd < 0) error("ERROR on accept");
    pid = fork();
    if(pid < 0) error("ERROR on fork");
    if(pid == 0){
      close(sockfd);
      dostuff(newsockfd);
      exit(0);
    }
    else close(newsockfd);
  }
  close(sockfd);
  return 0; /* we never get here */
}

void error(const char *msg){
    perror(msg);
    exit(1);
}

/******** DOSTUFF() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/

int dostuff (int sock){
  int n;
  int num = 0;
  double result;
  char buffer[256];
  char *ops[256]; // stores operands
  bzero(buffer,256);
  n = read(sock,buffer,255);
  if(n < 0) error("ERROR reading from socket");
  printf("Here is the message: %s\n",buffer);
  n = write(sock, "I got your message\n", 19);
  if(n < 0) error("ERROR writing to socket");
  num = tokenize(buffer, ops); // tokenize the input
  if(num != 3){ // should only have three tokens, otherwise invalid number of ops
    n = write(sock,"Invalid number of commands recieved\n",36);
    if (n < 0) error("ERROR writing to socket");
    error("ERROR recieved invalid number of commands"); // not 3 commands
  }
  if (ops[0][1] != '\0') error("ERROR invalid operation"); // operation only 1 char long, so [0][1] shoud be \0
  if(isNumber(ops, 1)) error("ERROR operand 1 invalid");
  if(isNumber(ops, 2)) error("ERROR operand 2 invalid");
  result = calc(ops); // calculate output
  snprintf(buffer, 256, "The result of the operation: %f\n", result);
  printf("The result: %f\n", result);
  n = write(sock, buffer, strlen(buffer));
  if(n < 0) error("ERROR writing to  socket");
  return 1;
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

double calc(char *cmd[]){
  double d;
  char x = cmd[0][0]; /* get the operation */
  int y = strtol(cmd[1], NULL, 0);
  int z = strtol(cmd[2], NULL, 0);
  switch(x){
  case '+':
    printf("+\n");
    d = y+z;
    break;
  case '-':
    printf("-\n");
    d = y-z;
    break;
  case '*':
    printf("*\n");
    d = y*z;
    break;
  case '/':
    printf("/\n");
    d = y/z;
    break;
  case '%':
    printf("%\n");
    d = y%z;
    break;
  default:
    error("ERROR with operation");
    break;
  }
  return d;
}

int isNumber(char *cmd[], int i){ // checks if the string is a number, i is string in array
  int j = 0;
  if(cmd[i][j] == '\0'){ // recieved empty string
    printf("NULL\n");
    return -1;
  }
  while((cmd[i][j] != '\0') && (cmd[i][j] != '\n')){ // runs until \0 or \n
    if((cmd[i][j] < 48) || (cmd[i][j] > 57)){ // char is outside number ascii value
      printf("ascii error\n");
      return 1; // return 1 on fail
    }
    printf("next\n");
    j++;
  }
  return 0; // returned if string is number
}

