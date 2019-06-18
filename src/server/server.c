#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>

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

    cli = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
    len = sizeof(*cli);

    printf("Server listening..\n");
  
    /*// Accept the data packet from client and verification 
    // Single client version
    connfd = accept(sockfd, cli, &len); 
    if (connfd < 0) { 
        perror("server could not accept connection");
        exit(-4); 
    } 
    else{
        printf("Server acccepted the client...\n"); 
    }
    // SERVER READY AND ACCEPTED CONNECTION, LISTENING...
    getData(connfd);*/

    //Multi-client version
    int multiconfd[CLIENT_MAX];

    fd_set readfds;
    int max_sd, activity;

    char buffer[BUFF_MAX];
    char buffToSend[BUFF_MAX+30];
    char idGadjo[30];
    char tmpPort[6];
    int n = 0;

    for(int i = 0; i < CLIENT_MAX; ++i){
        multiconfd[i] = 0;
    }

    while(1){
        //Gestion des pelos déjà connectés
        FD_ZERO(&readfds);
        
        FD_SET(sockfd, &readfds);
        max_sd = sockfd;

        for(int i = 0; i < CLIENT_MAX; ++i){
            if(multiconfd[i] > 0){
                FD_SET(multiconfd[i], &readfds);
            }

            if(multiconfd[i] > max_sd){
                max_sd = multiconfd[i];
            }
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if((activity < 0)){
            perror("CA VA PAS SE PASSER COMME CA");
        }

        //Connexion entrante
        if(FD_ISSET(sockfd, &readfds)){
            connfd = accept(sockfd, (struct sockaddr *)cli, (socklen_t*)&len);
            if (connfd < 0) { 
                perror("server could not accept connection");
                exit(-4); 
            } else{
                for(int i = 0; i < CLIENT_MAX; ++i){
                    if(multiconfd[i] == 0){
                        multiconfd[i] = connfd;
                        printf("Server accepted a new connection on socket #%d @[%s:%d]\n", connfd, inet_ntoa(cli->sin_addr), ntohs(cli->sin_port));
                        for(int j = 0; j < CLIENT_MAX; ++j){
                            if(i != j && multiconfd[j] != 0 && multiconfd[j] != connfd){
                                strcpy(idGadjo, "[");
                                strcat(idGadjo, inet_ntoa(cli->sin_addr));
                                strcat(idGadjo, ":");
                                sprintf(tmpPort, "%d", ntohs(cli->sin_port));
                                strcat(idGadjo, tmpPort);
                                strcat(idGadjo, "] ");
                                strcpy(buffToSend, idGadjo);
                                strcat(buffToSend, "Joined\0");
                                write(multiconfd[j], buffToSend, strlen(buffToSend));
                            }
                        }
                        break;
                    }
                }
            }
        }else{
            //Gestion des I/O sur les connexions existantes
            for(int i = 0; i < CLIENT_MAX; ++i){
                connfd = multiconfd[i];

                if(FD_ISSET(connfd, &readfds)){
                    bzero(buffer, BUFF_MAX);
                    n = read(connfd, buffer, BUFF_MAX);
                    getpeername(connfd , (struct sockaddr*)cli , (socklen_t*)&len);
                    printf("Message reçu socket %d @[%s:%d]\n>> %s (%d Bytes)\n", connfd, inet_ntoa(cli->sin_addr), ntohs(cli->sin_port), buffer, n);

                    if(strcmp(buffer, "!exit") == 0){
                        write(connfd, "QUIT", 5);
                        printf("Gadjo déconnecté [%s:%d]\n", inet_ntoa(cli->sin_addr) , ntohs(cli->sin_port));
                        for(int j = 0; j < CLIENT_MAX; ++j){
                            if(i != j && multiconfd[j] != 0 && multiconfd[j] != connfd){
                                strcpy(idGadjo, "[");
                                strcat(idGadjo, inet_ntoa(cli->sin_addr));
                                strcat(idGadjo, ":");
                                sprintf(tmpPort, "%d", ntohs(cli->sin_port));
                                strcat(idGadjo, tmpPort);
                                strcat(idGadjo, "] ");
                                strcpy(buffToSend, idGadjo);
                                strcat(buffToSend, "Left\0");
                                write(multiconfd[j], buffToSend, strlen(buffToSend));
                            }
                        }
                        //Close the socket and mark as 0 in list for reuse
                        close( connfd );
                        multiconfd[i] = 0;
                    }else if(strcmp(buffer, "!stop") == 0){
                        printf("closing connexions\n");
                        for(int j = 0; j < CLIENT_MAX; ++j){
                            if(multiconfd[j] != 0){
                                write(multiconfd[j], "Server stopping now", 20);
                                close(multiconfd[j]);
                                multiconfd[j] = 0;
                            }
                        }
                        printf("closing server\n");
                        close(sockfd);
                        exit(0);
                    }else{
                        for(int j = 0; j < CLIENT_MAX; ++j){
                            if(i != j && multiconfd[j] != 0 && multiconfd[j] != connfd){
                                strcpy(idGadjo, "[");
                                strcat(idGadjo, inet_ntoa(cli->sin_addr));
                                strcat(idGadjo, ":");
                                sprintf(tmpPort, "%d", ntohs(cli->sin_port));
                                strcat(idGadjo, tmpPort);
                                strcat(idGadjo, "] ");
                                strcpy(buffToSend, idGadjo);
                                strcat(buffToSend, buffer);
                                write(multiconfd[j], buffToSend, strlen(buffToSend));
                            }
                        }
                        write(connfd, "OK", 3);
                    }
                }
            }
        }
    }

    // After chatting close the socket 
    close(sockfd); 
}