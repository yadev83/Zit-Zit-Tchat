#include <stdio.h>
#include <stdlib.h>

#include "sockets/socket.h"

int main(void){
    SocketManager *client = NULL;

    client = newSocket(PF_INET, SOCK_STREAM, 0);
    initSocket(client);
    newConnection(client, "127.0.0.1", IPPORT_USERRESERVED);
    connectClientSocket(client);

    sendString(client, "Hello There !");
    getString(client, 2);

    closeSocket(client);
    deleteSocket(client);

    return 0;
}