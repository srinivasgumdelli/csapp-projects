#include "servant.h"

int main(int argc, char **argv){
    selfAddr.sin_addr = INADDR_ANY;

    initializeList();

    serverConnect(argv);
}

void serverConnect(char **argv){
    servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&servAddr, '\0', sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(DEFAULT_PORT);

    inet_pton(AF_INET, argv[1], &servAddr.sin_addr);

    fd_set cfd;
    FD_ZERO(&cfd);
    FD_SET(selfSock, &cfd);

    select(selfSock + 1, &cfd, NULL, NULL, NULL);

    connect(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr));

    unpackaging();      // recieve data from central server
    int z;
    for( z = 0; z < MAX_CLIENT; z++){
        peerConnect(onlineList[z].status, i, UPDATING);
    }

    while(1){
        char curAddr[INET_ADDRSTRLEN];
        int curStatus = ONLINE;

        read(servSock, &buffer, BUFFER_MAX);    // poll the server

        if( strcmp(buffer, "UPDATE") == 0 ){
            read(servSock, curAddr, INET_ADDRSTRLEN);       // get the address of the update
            read(servSock, curStatus, sizeof(curStatus));   // get the status update

            int i;
            for( i = 0; i < MAX_CLIENT; i++){
                if(strcmp(onlineList[i].addr, curAddr) == 0){   // if the address is old
                    onlineList[i].status = curStatus;

                    peerConnect(curStatus, i, UPDATING);
                }

                if(strcmp(onlineList[i].addr, "") == 0){        // if the address is new
                    onlineList[i].addr = curAddr;
                    onlineList[i].status = curStatus;

                    peerConnect(curStatus, i, 0);
                }
            }
        }

        peerPolling();
    }
}

void peerPolling(){
    int i;
    for( i = 0; i < MAX_CLIENT; i++ ){
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(sockets[i], &fds);

        select(sockets[i] + 1, &fds, NULL, NULL, 1);     // block for a second

        char command[BUFFER_MAX];
        printf("Download File From Peer %s (y/n): ", onlineList[i].addr);
        scanf("%s", command);
        if( strcmp(command, "y") == 0 ){
            printf("What's the filename?\n");
            fgets(command, BUFFER_MAX, stdin);
            *(strchr(command, '\n')) = 0;

            strcpy(buffer, "TRANSERTOME");
            write(sockets[i], buffer, BUFFER_MAX);  // alert peer that sending is occuring

            write(sockets[i], command, BUFFER_MAX); // send filename to peer

            read(sockets[i], buffer, BUFFER_MAX);   // read confirmation
            if( strcmp(buffer, "CONFIRM") == 0){
                strcpy(buffer, "GOAHEAD");
                write(sockets[i], buffer, BUFFER_MAX);  // tell the peer to start sending

                fileDownload(int i, command);
            }else{
                if( strcmp(buffer, "NOGO") == 0)
                    printf("Peer doesn't have the file\n");
            }

        }else{
            read(sockets[i], buffer, BUFFER_MAX);   // poll socket

            if(strcmp(buffer, "TRANSFERTOME") == 0){
                read(sockets[i], buffer, BUFFER_MAX)    // read filename
                if( access(buffer, F_OK & R_OK) < 0 ){
                    printf("Can't access requested file...");

                    strcpy(buffer, "NOGO");
                    write(sockets[i], buffer, BUFFER_MAX);
                }else{
                    char filename[BUFFER_MAX];
                    strcpy(filename, buffer);
                    printf("Sending %s to peer\n", filename);

                    fileUpload(i, filename);
                }
            }
        }
    }
}

void fileUpload(int i, char *fileName){
    int bytesRead, i, fileNo;
    char tempBuffer[BUFFER_MAX];
    bzero(buffer, BUFFER_MAX);

    umask(0000);
    fileNo = open(fileName, O_RDONLY, 0664);    // open file for reading only

    strcpy(buffer, "CONFIRM");
    write(sockets[i], buffer, BUFFER_MAX);  // tell the peer the send is about to start

    read(sockets[i], buffer, BUFFER_MAX);

    while(strcmp(buffer, "GOAHEAD") == 0){  // loop while peer says GOAHEAD
        bytesRead = read(fileNo, tempBuffer, BUFFER_MAX);   // read file chunk from file
        write(sockets[i], tempBuffer, BUFFER_MAX);  // send file chunk to peer
        if(bytesRead < BUFFER_MAX)
            break;  // break when buffer is only partially filled, meaning it's the last read
    }

    close(fileNo);
    printf("File transfer completed\n");
}

void fileDownload(int i, char *fileName){
    int bytesRead, i, fileNo;
    char tempBuffer[BUFFER_MAX];
    bzero(buffer, BUFFER_MAX);

    umask(0000);
    fileNo = open(fileName, O_CREATE | O_APPEND, 0664);     // open new file or adds to old file, delete your files to make so no overwriting occurs!

    do{
        bytesRead = read(sockets[i], tempBuffer, BUFFER_MAX);
        write(fileNo, tempBuffer, BUFFER_MAX);

        strcpy(buffer, "GOAHEAD");
        write(sockets[i], buffer, BUFFER_MAX);

        }while(bytesRead == BUFFER_MAX);    // loop while buffer is full, when buffer is partially filled that means it's the last read

        close(fileNo);
    }
}

void peerConnect(int curStatus, int i, int isUpdate){
    if(curStatus == 1){ // online, then do connect/accept
        int isOwn = strcmp(onlineList[i].addr, inet_ntoa(selfAddr.sin_addr));
        int isNull = strcmp(onlineList[i].addr, "");

        if(isOwn != 0 && isNull != 0){  // if address is not your own or null
            struct sockaddr_in clntAddr;
            memset(&clntAddr, 0, sizeof(clntAddr));
            clntAddr.sin_family = AF_INET;
            clntAddr.sin_port = htons(DEFAULT_PORT + i);

            if(isUpdate != UPDATING){   // if the address is OLD, connect to it
                inet_pton(AF_INET, onlineList[i].addr, &clntAddr.sin_addr);

                connect(sockets[i], (struct sockaddr *)&clntAddr.sin_addr, sizeof(clntAddr));
            }else{  // if the address is NEW
                clntAddr.sin_addr = INADDR_ANY;

                bind(sockets[i], (struct sockaddr *)&clntAddr, sizeof(clntAddr));
                listen(sockets[i], 0);

                socklen_t socklen = sizeof(clntAddr);
                accept(sockets[i], (struct sockaddr *)&clntAddr, &socklen);
            }
        }
    }else{  // offline, close socket
        printf("Peer %d going offline\n", sockets[i]);
        close(sockets[i]);
    }
}

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

void unpackaging(){
    char curAddr[INET_ADDRSTRLEN];
    int curStatus = ONLINE;
    strcpy(curAddr, inet_ntoa(selfAddr.sin_addr));

    if( write(servSock, curAddr, INET_ADDRSTRLEN) < 0 ){
        error("unpackaging: Reporting Address to Server Failed");
    }
    if( read(servSock, &buffer, BUFFER_MAX) < 0 && strcmp(buffer, "CORRECT") == 0 ){
        error("upackaging: Server Failed to Get Address");
    }
    if( write(servSock, curStatus, sizeof(curStatus)) < 0 ){
        error("unpackaging: Reporting Status to Server Failed");
    }

    int i;
    for( i = 0; i < MAX_CLIENT; i++){
        curAddr = onlineList[i].addr;
        curStatus = onlineList[i].status;

        if( read(servSock, curAddr, INET_ADDRSTRLEN) < 0 )
            error("unpackaging: Reading Online List Address Failed");
        if( write(servSock, &buffer, BUFFER_MAX) < 0 )
            error("unpackaging: Writing Confirm Address Failed");
        if( read(servSock, curStatus, sizeof(curStatus)) < 0 )
            error("unpackaging: Reading Online List Status Failed");
        if( write(servSock, &buffer, BUFFER_MAX) < 0 )
            error("unpackaging: Writing Confirm Status Failed");
    }

    for(i = 0; i < MAX_CLIENT; i++)
        printf("\t%s\t%d\n", onlineList[i].addr, onlineList[i].status);
}
