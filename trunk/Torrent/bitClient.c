/*
Made by Kelsey Yuen, 2012
This module does the servant part of the program. Acts as both client and server. Decentralized.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define defaultServAddr "127.0.0.1"
#define setPortNumber 5120
#define BUFFER_MAX 256
#define MAX_CLIENT 50
#define ON 1
#define OFF -1

typedef struct foo {char name[BUFFER_MAX], int status} list;

void error(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

/*
Connect to Server, get List and then disconnect
Connect to peers on the List
Fancy Stuff
Disconnect from peers, connect to server and edit list (not connected)
If last peer, send data back to server
*/

int main(){
    list onlineList[MAX_CLIENT];
    // do stuff
    bootUp();

    exit(EXIT_SUCCESS);
}

list bootUp(){
    // bootUp program by requesting from set server
    char *serverAddress = defaultServAddr;
    int portNo = setPortNumber;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Socket creation failed...");
    }

    struct sockaddr_in servAddr;
    memset(&servAddr, '\0', sizeof(servAddr));  // zero out the struct
    servAddr.sin_family = AF_INET;  // set for IPv4
    servAddr.sin_port = htons(portNo);  // convert the port number

    if(connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0){
        error("Connection failed...");
    }

    const char *connectMsg = "Connected to Server";
    int bytes = write(sockfd, connectMsg, strlen(connectMsg));
    if(bytes < 0){
        error("Write to socket failed...");
    }
    bytes = -1;

    list onlineList[MAX_CLIENT];
    bytes = read(sockfd, &onlineList, sizeof(list) * MAX_CLIENT);
    if(bytes < 0){
        error("Read from socket fail...");
    }
    printf("%s\n", buffer); // replace with store function
    close(sockfd);  // close the server connection after done

    return &onlineList;
}

void requestConnection(list *onlineList){
    int i, portNo;
    int clientSock[MAX_CLIENT];

    for(i = 0; i < MAX_CLIENT; i++){
        if(onlineList[i].status > 0){
            clientSock[i] = socket(AF_INET, SOCK_STREAM, 0);    // create socket
            if(clientSock[i] < 0){
                error("Client socket creation failed");
            }
            // TBA: getting the portNo

            struct sockaddr_in servAddr;
            memset(&servAddr, '\0', sizeof(servAddr));
            servAddr.sin_family = AF_INET;
            servAddr.sin_port = htons(portNo);

            if (connect(clientSock[i], (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0){
                error("Client connection failed");
            }
            printf("Client connected to %d", clientSock[i].name);
        }
    }
}