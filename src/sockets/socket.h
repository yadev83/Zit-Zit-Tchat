#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct SocketManager SocketManager;

struct SocketManager{
    //Contiendra les données du socket
    int descSocket;

    //Domaine du socket (PF_INET pour IPv4 et AF_INET6 pour IPv6)
    int domain;
    //Type du socket (SOCK_STREAM pour TCP ou SOCK_DGRAM pour UDP ou SOCK_RAW pour des protocoles couche réseau)
    int type;
    //Protocole utilisé par le socket
    int protocol;

    struct sockaddr_in distantConnection;
    socklen_t addrLength;

    char *address;
    unsigned short int port;
};

SocketManager *newSocket(int domain, int type, int protocol);
void initSocket(SocketManager *client);

void newConnection(SocketManager *client, char *address, unsigned short int port);
void connectSocket(SocketManager *client);

void sendString(SocketManager *client, char *msg);
void getString(SocketManager *client, int size);

void closeSocket(SocketManager *client);
void deleteSocket(SocketManager *client);

#endif //SOCKET_H