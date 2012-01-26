// MADE BY KELSEY YUEN 2012, NOT FOR REPRODUCTION
#ifndef SERVANT_H_INCLUDED
#define SERVANT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define defaultServAddr "127.0.0.1"
#define setPortNumber 5024
#define BUFFER_MAX 256
#define MAX_CLIENT 50
#define ON 0
#define OFF -1

typedef struct {char *name; int status;} list;

list onlineList[MAX_CLIENT];

void error(const char *);
void bootUp();      // Set up server, bind port number and IP address
void initialize();  // Connect to main server, retrieve list, then disconnect from main server
void peerConnect(); // go through list of peers and try to connect to all of them


#endif // SERVANT_H_INCLUDED
