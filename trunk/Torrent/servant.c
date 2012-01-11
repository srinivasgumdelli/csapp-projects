#include "servant.h"

typedef struct {char name[BUFFER_MAX]; int status;} list;

list onlineList[MAX_CLIENT];

void error(const char *);
void bootUp();      // Set up server, bind port number and IP address
void initialize();  // Connect to main server, retrieve list, then disconnect from main server
void peerConnect(); // go through list of peers and try to connect to all of them

int main(){
    bootUp();
    initialize();
    peerConnect();

    exit(EXIT_SUCCESS);
}

void error(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void bootUp(){
    int selfSock = socket(AF_INET, SOCK_STREAM, 0);
    if(selfSock < 0){
        error("BootUp: Socket creation failed");
    }

    struct sockaddr_in sock;
    memset(&sock, '\0', sizeof(sock));
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = htonl(INADDR_ANY);
    sock.sin_port = htons(setPortNumber);
    if(bind(selfSock, (struct sockaddr *)&sock, sizeof(sock)) < 0){
        error("BootUp: Binding failed");
    }

    if(listen(selfSock, MAX_PENDING) < 0){
        error("BootUp: Listening failed");
    }

    while(1){
        struct sockaddr_in clntAddr;
        socklen_t clntAddrLen = sizeof(clntAddr);

        int clntSock = accept(selfSock, (struct sockaddr *)&clntAddr, &clntAddrLen);
        if(clntSock < 0){
            error("BootUp: Accept failed");
        }
    }
}

void initialize(){
    int servfd = socket(AF_INET, SOCK_STREAM, 0);

    // connect to main server, etc.
}

void peerConnect(){
    int i;
    for(i = 0; i < MAX_CLIENT; i++){
        // do stuff
    }
}
