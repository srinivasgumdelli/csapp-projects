#include "mainHeader.h"

int main(){
    initializeList();

    newStatus = 0;

    serverConnect();

    cleanUp();
}

void serverConnect(){
    int i;
    for( i = 0; i < MAX_CLIENT; i++){
        sockets[i].sockfd = -1;
        sockets[i].addr = "";
    }

    selfSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&selfAddr, 0, sizeof(selfAddr));
    selfAddr.sin_family = AF_INET;
    selfAddr.sin_addr = INADDR_ANY;
    selfAddr.sin_port = htons(DEFAULT_PORT);

    bind(selfSock, (struct sockaddr *)&selfAddr, sizeof(selfAddr));
    listen(selfSock, 0);

    while(1){
        socklen_t socklen = sizeof(selfAddr);
        int clntSock = accept(selfSock, (struct sockaddr *)&selfAddr, &socklen);    // block on accept

        packaging();

        for( i = 0; i < MAX_CLIENT; i++)
            if(strcmp(sockets[i].addr, newAddr) == 0)
                break;

        if( i == MAX_CLIENT ){
            for(i = 0; i < MAX_CLIENT; i++){
                if(strcmp(sockets[i].addr, "") == 0){
                    sockets[i].addr = newAddr;
                    sockets[i].sockfd = clntSock;
                }
            }
        }else
            sockets[i].sockfd = clntSock;

        int childProcCount = 0;
        pid_t processID = fork();

        if( processID == 0 ){   // child process tells clients UPDATE
            close(selfSock);    // close server socket

            for(i = 0; i < MAX_CLIENT; i++){
                int isSame = strcmp(sockets[i].addr, newAddr);
                int isNull = strcmp(sockets[i].addr, "");

                if(isSame != 0 && isNull != 0){
                    strcpy(buffer, "UPDATE");
                    write(sockets[i].sockfd, buffer, BUFFER_MAX);
                    write(sockets[i].sockfd, newAddr, INET_ADDRSTRLEN);
                    write(sockets[i].sockfd, newStatus, sizeof(newStatus));
                }
            }

            exit(EXIT_SUCCESS);
        }

        childProcCount++;
        while(childProcCount){
            processID = waitpid((pid_t) -1, NULL, WNOHANG);
            if( processID == 0 )
                break;
            else
                childProcCount--;
        }

    }
}

/*void serverConnect(){
    int childProcCount = 0;

    if( (selfSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
        error("Socket Creation Failed");

    memset(&selfAddr, 0, sizeof(selfAddr));
    selfAddr.sin_family = AF_INET;
    selfAddr.sin_addr = INADDR_ANY;
    selfAddr.sin_port = htons(DEFAULT_PORT);

    if( bind(selfSock, (struct sockaddr *)&selfAddr, sizeof(selfAddr)) < 0)
        error("Binding Failed");
    if( listen(selfSock, 0) < 0 )
        error("Listening Failed");

    while(1){
        socklen_t socklen = sizeof(selfAddr);
        int clntSock = accept(selfSock, (struct sockaddr *)&selfAddr, &socklen));

        pid_t processID = fork();
        if (processID == 0){    // child process
            close(servSock);

            // handle the new client
            packaging();

            int i;
            for( i = 0; i < MAX_CLIENT; i++){
                int isNull = strcmp(onlineList[i].addr, "");
                int isSame = strcmp(onlineList[i].addr, newAddr);

                if( isNull != 0 && isSame != 0 ){  // if client address exists and is not the same
                    bzero(buffer, BUFFER_MAX);
                    strcpy(buffer, "UPDATE");
                    write(sockets[i], buffer, BUFFER_MAX);  // tell client update is occuring
                    write(sockets[i], newAddr, INET_ADDRSTRLEN);    // tell client address of update
                    write(sockets[i], newStatus, sizeof(newStatus));    // tell client new status
                }
            }
            // stop

            exit(EXIT_SUCCESS);
        }

        close(clntSock);
        childProcCount++;

        while(childProcCount){
            processID = waitpid((pid_t) - 1, NULL, WNOHANG);
            if(processID == 0)
                break;
            else
                childProcCount--;
        }
    }

    /*int f = fork();
    if( f != 0 ){   // parent redirects connections
        while(1){
            socklen_t socklen = sizeof(selfAddr);
            int clientSock;
            if( (clientSock = accept(selfSock, (struct sockaddr *)&selfAddr, &socklen)) < 0 )
                error("First Connection Failed");
            printf("Connected to %d\n", clientSock);

            int tempPort = DEFAULT_PORT + clientNumber;
            write(clientSock, tempPort, sizeof(tempPort));  // tell client new port number
            clientNumber++;

            close(clientSock);
        }
    }else{  // child does the updating
        struct sockaddr_in clntAddr;
        memset(&clntAddr, 0, sizeof(clntAddr));
        clntAddr.sin_family = AF_INET;
        clntAddr.sin_addr = INADDR_ANY;
        clntAddr.sin_port = DEFAULT_PORT + clientNumber;

        socklen_t len = sizeof(clntAddr);
        int clntSock;

        bind(clntSock, (struct sockaddr *)&clntAddr, sizeof(clntAddr));
        listen(clntSock, 0);
        int newSock = accept(clntSock, (struct sockaddr *)&clntAddr, &len);

        int i;
        for( i = 0; i < MAX_CLIENT; i++){   // go through list and update
            int isNull = strcmp(onlineList[i].addr, "");
            int isSame = strcmp(onlineList[i].addr, newAddr);

            if( isNull != 0 && isSame != 0 ){  // if client address exists and is not the same
                bzero(buffer, BUFFER_MAX);
                strcpy(buffer, "UPDATE");
                write(sockets[i], buffer, BUFFER_MAX);  // tell client update is occuring
                write(sockets[i], newAddr, INET_ADDRSTRLEN);    // tell client address of update
                write(sockets[i], newStatus, sizeof(newStatus));    // tell client new status
            }

        }

        exit(EXIT_SUCCESS); // terminate the child process

    }
}*/

void error(char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void initializeList(){
    int z;
    for(z = 0; z < MAX_CLIENT; z++){
        onlineList[z].addr = " ";
        onlineList[z].status = 0;
    }
}

void packaging(){
  strcpy(buffer, "CORRECT");

  if( read(clientSock, newAddr, INET_ADDRSTRLEN) < 0 )
    error("packaging: Read Client Address Failed");
  if( write(clientSock, &buffer, BUFFER_MAX) < 0 )
    error("packaging: Report Correct Address Failed");
  if( read(clientSock, &newStatus, sizeof(newStatus)) < 0 )
    error("packaging: Read Client Status Failed");

  int i;
  for(i = 0; i < MAX_CLIENT; i++){
    if( strcmp(onlineList[i].addr, newAddr) == 0 ){
      onlineList[i].status = newStatus;'
      break;
    }
    if( strcmp(onlineList[i].addr, "") == 0 ){
        onlineList[i].addr = newAddr;
        onlineList[i].status = newStatus;
        break;
    }
  }

  for(i = 0; i < MAX_CLIENT; i++){
      newAddr = onlineList[i].addr;
      newStatus = onlineList[i].status;

      if( write(clientSock, newAddr, INET_ADDRSTRLEN) < 0 )
          error("packaging: Writing Online List Address Failed");
      if( read(clientSock, &buffer, BUFFER_MAX) < 0 )
          error("packaging: Confirm Correct Address Failed");
      if( write(clientSock, newStatus, sizeof(newStatus)) < 0 )
          error("packaging: Writing Online List Status Failed");
      if( read(clientSock, &buffer, BUFFER_MAX) < 0 )
          error("packaging: Confirm Correct Status Failed");
  }
}

void cleanUp(){
    int i;
    for( i = 0; i < MAX_CLIENT; i++ )
        close(sockets[i].sockfd);
    close(selfSock);
    exit(EXIT_SUCCESS);
}
