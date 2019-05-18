#ifndef CLIENT_H
#define CLIENT_H

#define BUFF_MAX 100
#define PORT 5000

/* ERROR CODE LIST :
-1 = socket creation failed
-2 = connection to the server failed
*/

void sendData(int sockfd);
struct sockaddr_in *newClient(int domain, in_addr_t addr, int port);

#endif //CLIENT_H