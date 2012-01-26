#ifndef SERVANT_H_INCLUDED
#define SERVANT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>

#define DEFAULT_PORT 5000
#define BUFFER_MAX 256
#define MAX_CLIENT 4

#define UPDATING 1

typedef struct {char *addr; int status;} list;
list onlineList[MAX_CLIENT];

struct sockaddr_in servAddr;
struct sockaddr_in selfAddr;

int servSock;   // socket for central server
int sockets[MAX_CLIENT];    // sockets for peers

char buffer[BUFFER_MAX];

void serverConnect(char **argv);
void peerPolling();
void fileUpload(int i, char *filename);
void fileDownload(int i, char *filename);
void peerConnect(int curStatus, int i, int isUpdate);
void error(char *msg);
void initializeList();
void unpackaging();

#endif // SERVANT_H_INCLUDED
