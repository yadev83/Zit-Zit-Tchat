#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h> 
#include <netinet/in.h> 

#include <sys/socket.h> 
#include <sys/types.h> 

#include "server.h"

void getData(int sockfd){
    char buffer[BUFF_MAX];
    int n = 0;

    while(1){
        bzero(buffer, BUFF_MAX);

        n = read(sockfd, buffer, BUFF_MAX);
        printf("Message reçu : %s (%d Bytes)\n", buffer, n);
        
        if(strcmp(buffer, "exit") == 0){
            write(sockfd, "QUIT", 5);
            printf("SERVER CLOSING NOW\n");
            break;
        }else{
            write(sockfd, "OK", 3);
        }
    }
}

struct sockaddr_in *newServ(int domain, in_addr_t addr, int port){
    struct sockaddr_in *servaddr = NULL;
    
    servaddr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
    bzero(servaddr, sizeof(struct sockaddr_in)); 

    servaddr->sin_family = domain; 
    servaddr->sin_addr.s_addr = htonl(addr); 
    servaddr->sin_port = htons(port); 
  
    return servaddr;
}

//Server main function
int main(void){
    int sockfd, connfd, len; 
    struct sockaddr_in *servaddr;
    struct sockaddr_in *cli; 
   
    // socket connecté en mode IPv4
    sockfd = socket(PF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        perror("socket creation failed");
        exit(-1); 
    } 
    else{
        printf("Socket successfully created..\n"); 
    }

    // assign IP, PORT 
    servaddr = newServ(PF_INET, INADDR_ANY, PORT);

    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, servaddr, sizeof(struct sockaddr_in))) != 0) { 
        perror("socket bind failed");
        exit(-2); 
    } 
    else{
        printf("Socket successfully binded..\n"); 
    }

    // Now server is ready to listen and verification 
    if ((listen(sockfd, CLIENT_MAX)) != 0) { 
        perror("listen failed");
        exit(-3); 
    } 
    else{
        printf("Server listening..\n");
    }
    cli = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
    len = sizeof((*cli)); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, cli, &len); 
    if (connfd < 0) { 
        perror("server could not accept connection");
        exit(-4); 
    } 
    else{
        printf("Server acccepted the client...\n"); 
    }

    // SERVER READY AND ACCEPTED CONNECTION, LISTENING...
    getData(connfd); 
  
    // After chatting close the socket 
    close(sockfd); 
}