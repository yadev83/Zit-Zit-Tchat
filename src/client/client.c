#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <sys/socket.h>

#include "client.h"

void sendData(int sockfd){
    char buffer[BUFF_MAX]; 
    int n = 0; 
    while(1){ 
        bzero(buffer, sizeof(buffer)); 
        printf("> "); 
        n = 0; 

        //Get characters
        while ((buffer[n++] = getchar()) != '\n');
        buffer[n-1] = '\0';

        write(sockfd, buffer, sizeof(buffer)); 

        printf("message sent to server <%s>\n", buffer);

        bzero(buffer, sizeof(buffer)); 
        read(sockfd, buffer, sizeof(buffer)); 
        printf("SERVER RESPONDED : %s\n", buffer); 

        if ((strncmp(buffer, "QUIT", 4)) == 0) { 
            printf("Server closed the connection, now closing client...\n"); 
            break; 
        } 
    } 
}

struct sockaddr_in *newClient(int domain, in_addr_t addr, int port){
    struct sockaddr_in *servaddr = NULL;
    
    servaddr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
    bzero(servaddr, sizeof(struct sockaddr_in)); 

    servaddr->sin_family = domain; 
    servaddr->sin_addr.s_addr = addr; 
    servaddr->sin_port = htons(port); 
  
    return servaddr;
}

int main(int argc, char *argv[]){
    int sockfd, connfd; 
    struct sockaddr_in *servaddr;

    int addr_set;

    if(argc > 1){
        printf("Tentative de connexion au serveur à l'adresse %s\n", argv[1]);
        addr_set = 1;
    }else{
        printf("WARNING : Aucune adresse n'a été spécifiée.\nTentative de connexion sur le réseau local...\n");
        addr_set = 0;
    }

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
    if(addr_set == 1)
        servaddr = newClient(PF_INET, inet_addr(argv[1]), PORT);
    else
        servaddr = newClient(PF_INET, inet_addr("127.0.0.1"), PORT);

    // connect the client socket to server socket 
    if (connect(sockfd, servaddr, sizeof(*servaddr)) != 0) { 
        perror("connection to the server failed");
        exit(-2); 
    } 
    else{
        printf("connected to the server [%s:%d]\n", "127.0.0.1", PORT); 
    }

    // CONNECTED TO SERVER READY TO TALK
    sendData(sockfd); 
  
    // close the socket 
    close(sockfd); 
}
        