#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket.h"


SocketManager *newSocket(int domain, int type, int protocol){
    SocketManager *sock = (SocketManager *) malloc(sizeof(SocketManager));

    sock->domain = domain;
    sock->type = type;
    sock->protocol = protocol;

    return sock;
}

void initSocket(SocketManager *sock){
    sock->descSocket = socket(sock->domain, sock->type, sock->protocol);

    if(sock->descSocket < 0){
        perror("initSocket()");
        exit(-1);
    }else{
        printf("Socket client initialisé avec succès ! (%d)\n", sock->descSocket);
    }
}

void newConnection(SocketManager *sock, char *address, unsigned short int port){
    sock->port = port;
    sock->address = (char *) malloc(sizeof(char) * strlen(address));
    strcpy(sock->address, address);
}

void newServer(SocketManager *sock, unsigned short int port){
    sock->port = port;
    sock->address = NULL;
}

void connectClientSocket(SocketManager *sock){
    sock->addrLength = sizeof(sock->distantConnection);
    memset(&(sock->distantConnection), 0x00, sock->addrLength);
    sock->distantConnection.sin_family = PF_INET;
    sock->distantConnection.sin_port = htons(sock->port);
    inet_aton(sock->address, &(sock->distantConnection.sin_addr));

    if((connect(sock->descSocket, (struct sockaddr *)&(sock->distantConnection), (sock->addrLength)) == -1)){
        perror("connect");
        close(sock->descSocket);
        exit(-2);
    }

    printf("Connecté au serveur [%s:%d] avec succès\n\n", sock->address, sock->port);
}

void connectServerSocket(SocketManager *sock){
    sock->addrLength = sizeof(sock->distantConnection);
    memset(&(sock->distantConnection), 0x00, sock->addrLength);
    sock->distantConnection.sin_family = PF_INET;
    sock->distantConnection.sin_addr.s_addr = htonl(INADDR_ANY);
    sock->distantConnection.sin_port = htons(sock->port);

    if(bind(sock->descSocket, (struct sockaddr *)&(sock->distantConnection), sock->addrLength)){
        perror("bind");
        exit(-2);
    }

    printf("Serveur en écoute sur [%s:%d] avec succès\n\n", sock->address, sock->port);
}

void serverListener(SocketManager *server, int limit){
    if(listen(server->descSocket, limit) < 0){
        perror("listen");
        exit(-3);
    }

    printf("Socket placée en écoute passive ...\n");

    SocketManager *distant = newSocket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in income;
    //Serveur en attente indéfiniment
    while(1){
        printf("Attente d'une connexion (Ctrl+C pour fermer le serveur)\n\n");
        distant->descSocket = accept(server->descSocket, (struct sockaddr *)&(income), &(server->addrLength));
        if (distant->descSocket < 0){
            perror("accept");
            closeSocket(distant);
            closeSocket(server);
            exit(-4);
        }else{
            getString(distant, 100);
            sendString(distant, "ok");
        }
    }
}

void sendString(SocketManager *sock, char *msg){
    int bytesNb = write(sock->descSocket, msg, strlen(msg));

    switch(bytesNb){
        case -1:
            perror("write");
            close(sock->descSocket);
            exit(-3);
        break;

        case 0:
            fprintf(stderr, "Le socket à été fermé !\n\n");
            close(sock->descSocket);
            exit(0);
        break;

        default:
            printf("Message \"%s\" envoyé avec succès (%d bytes)\n", msg, bytesNb);
        break;
    }
}

void getString(SocketManager *sock, int size){
    char *recept = (char *) malloc(sizeof(char) * size);
    int bytesNb = read(sock->descSocket, recept, sizeof(char) * size);

    switch(bytesNb){
        case -1:
            perror("read");
            closeSocket(sock);
            exit(-4);
        break;

        case 0:
            fprintf(stderr, "La socket à été fermée !\n\n");
            closeSocket(sock);
        break;

        default:
            printf("Message reçu depuis la connexion distante : \"%s\" (%d bytes)\n", recept, bytesNb);
        break;
    }
}

void closeSocket(SocketManager *sock){
    close(sock->descSocket);
    printf("\nSocket client fermé avec succès ! (%d)\n", sock->descSocket);
}

void deleteSocket(SocketManager *sock){
    free(sock);
    sock = NULL;

    printf("Socket supprimé avec succès\n");
}

