/* client.c
 *
 * CS 270-01.Bolden..........Ethan Hinkle
 * 26 November, 2021........hink9661@vandals.uidaho.edu
 *
 * This is the client c file for the assigment 4 creating a server client
 * system in C
 *--------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg){
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[]){
  int sockfd, portno, n; 
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];
  if(argc < 3){
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
  }
  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) error("ERROR opening socket");
  server = gethostbyname(argv[1]);
  if(server == NULL){
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
  if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");

  printf("Enter the operator followed by the two operands: ");
  bzero(buffer,256); // clear buffer
  fgets(buffer,255,stdin); // get user input
  n = write(sockfd,buffer,strlen(buffer)); // write to the server
  if(n < 0) error("ERROR writing to socket");
  
  bzero(buffer,256);
  n = read(sockfd,buffer,255); // read returned value from server
  if(n < 0) error("ERROR reading from socket");
  printf("%s\n",buffer); // prints server message, either result or error

  close(sockfd); // terminate after one use, requires relaunch each time
  return 0;
}
