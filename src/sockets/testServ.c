#include <stdio.h>
#include <stdlib.h>

#include "socket.h"

int main(void){
    SocketManager *server = NULL;
    server = newSocket(PF_INET, SOCK_STREAM, 0);
    initSocket(server);
    newServer(server, IPPORT_USERRESERVED);
    connectServerSocket(server);

    serverListener(server, 5);

    closeSocket(server);
    deleteSocket(server);
}