#include <stdio.h>
#include <stdlib.h>

#include "socket.h"
#include "../tools/input.h"

int main(int argc, char *argv[]){
    SocketManager *client = NULL;
    int readOut = 0;

    client = newSocket(PF_INET, SOCK_STREAM, 0);
    initSocket(client);
    newConnection(client, argv[1], IPPORT_USERRESERVED);
    connectClientSocket(client);

    //sendString(client, "Opening Discussion !");
    //getString(client, 2);

    String str;
    do{
        getMessage(str);

        sendString(client, str);
        getString(client, 2);
        /*closeSocket(client);
        initSocket(client);
        newConnection(client, argv[1], IPPORT_USERRESERVED);
        connectClientSocket(client);*/
    }while(str[0] != '!' && str[1] != 'q');
    

    closeSocket(client);
    deleteSocket(client);

    return 0;
}