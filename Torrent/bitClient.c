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

void error(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(){
    // do stuff
    bootUp();

    exit(EXIT_SUCCESS);
}

void bootUp(){
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
    char buffer[BUFFER_MAX];
    int bytes = write(sockfd, connectMsg, strlen(connectMsg));
    if(bytes < 0){
        error("Write to socket failed...");
    }
    bytes = -1;
    bytes = read(sockfd, buffer, BUFFER_MAX - 1);
    if(bytes < 0){
        error("Read from socket fail...");
    }
    printf("%s\n", buffer); // replace with store function
    close(sockfd);  // close the server connection after done
}
