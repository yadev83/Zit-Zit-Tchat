#ifndef SERVER_H
#define SERVER_H

#define BUFF_MAX 100
#define CLIENT_MAX 5
#define PORT 5000

/* ERROR CODE LIST :
-1 = socket creation failed
-2 = socket bind failed
-3 = listen failed
-4 = server could not accept connection
*/

void getData(int sockfd);
struct sockaddr_in *newServ(int domain, in_addr_t addr, int port);

#endif //SERVER_H