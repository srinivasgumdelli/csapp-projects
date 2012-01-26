// MADE BY KELSEY YUEN 2012, NOT FOR REPRODUCTION
#ifndef SERVANT_H_INCLUDED
#define SERVANT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define DEFAULT_SERVER_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 5024
#define BUFFER_MAX 256
#define MAX_CLIENT 50
#define 0 SUCCESS
#define -1 FAIL

typedef struct fo {char addr[sizeof(struct ip) + 1]; int status;} list;
list onlineList[MAX_CLIENT];

int selfOut;    // client socket
int selfIn;     // server socket
struct sockaddr_in selfAddr;

void error(const char *);
void bootUp();      // Set up server, bind port number and IP address
void initialize();  // Connect to main server, retrieve list, then disconnect from main server
void peerConnect(); // go through list of peers and try to connect to all of them


#endif // SERVANT_H_INCLUDED
