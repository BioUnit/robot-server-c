#include <sys/socket.h>   //sockfd
#include <netinet/in.h>   //sockaddr
#include <netinet/ip.h>   //INADDR_ZNY
#include <stdio.h>
#include <string.h>
#include <unistd.h>       //sleep(), read(), write(), close()
#include "mygpio.h"

int main(int argc, char** argv){
   int sockfd, connfd, len;
   char buff[20] = {0};
   struct sockaddr_in servaddr = {
      .sin_family = AF_INET,
      .sin_port = htons(1000),
      .sin_addr.s_addr = htonl(INADDR_ANY)
   };
   struct sockaddr_in client;

   r_init();

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if(sockfd == -1){
      printf("Socket creation FAILED\r\n");
      return -1;
   } else {
      printf("Socket created\r\n");
   }

   if((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
      printf("Socket FAILED\r\n");
      return -1;
   } else {
      printf("Socket bind OK\r\n");
   }

   if((listen(sockfd, 5)) != 0){
      printf("Listening FAILED\r\n");
      return -1;
   } else {
      printf("Starting to listen\r\n");
   }

   len = sizeof(client);

   connfd = accept(sockfd, (struct sockaddr*)&client, &len);
   if(connfd < 0) {
      printf("Server accept failed\r\n");
      return -1;
   } else {
      printf("Server accepted the client\r\n");
   }

   while(1){
      read(connfd, buff, sizeof(buff));
      //printf("Client: %s\r\n", buff);
      if((buff[0] == 'L') && (buff[1]=='P')){
         r_move_left();
         memset(&buff, 0, 20);
      }
      if((buff[0] == 'R') && (buff[1]=='P')){
         r_move_right();
         memset(&buff, 0, 20);
      } 
      if((buff[0] == 'F') && (buff[1]=='P')){
         r_move_forward();
         memset(&buff, 0, 20);
      } 
      if((buff[0] == 'B') && (buff[1]=='P')){
         r_move_backward();
         memset(&buff, 0, 20);
      } 
      if((buff[0] == 'R') && (buff[1]=='R')){
         r_stop();
         memset(&buff, 0, 20);
      }
   }
   close(sockfd);
   return 0;
}


