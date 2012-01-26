#ifndef CENTRAL_H_INCLUDED
#define CENTRAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 5000
#define BUFFER_MAX 256
#define MAX_CLIENT 4

#define UPDATING 1

typedef struct {char *addr; int status;} list;
list onlineList[MAX_CLIENT];

typedef struct {int sockfd; char *addr;} data;
data sockets[MAX_CLIENT];

struct sockaddr_in selfAddr;

int selfSock;

char buffer[BUFFER_MAX];

char newAddr[INET_ADDRSTRLEN];
char newStatus;

void serverConnect();
void error(char *msg);
void initializeList();
void packaging();
void cleanUp();

#endif // CENTRAL_H_INCLUDED
