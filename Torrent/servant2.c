#include "servant.h"

int main(){
  bootUp();
  initialize();
  peerConnect();
  listenIn();

  exit(EXIT_SUCCESS);
}

void error(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void bootUp(){
    if((selfIn = socket(AF_INET, SOCK_STREAM, 0)) != SUCCESS){
        error("BootUp: Server-Purpose Socket Creation Failed");
    }else{
        printf("Server-Purpose Socket Descriptor: %d\n", selfIn);
    }

    memset(&selfAddr, 0, sizeof(selfAddr));
    selfAddr.sin_family = AF_INET;
    selfAddr.sin_addr.s_addr = INADDR_ANY;
    selfAddr.sin_port = htons(DEFAULT_PORT);
    int socklen = sizeof(selfAddr);
    if(bind(selfIn, (struct sockaddr *)&selfAddr, socklen) != SUCCESS){
        error("BootUp: Binding Failed");
    }

    if((selfOut = socket(AF_INET, SOCK_STREAM, 0)) != SUCCESS){
        error("BootUp: Client-Purpose Socket creation failed");
    }else{
        printf("Client-Purpose Socket Descriptor: %d\n", selfOut);
    }
}

void initialize(){
    if(int centralServer = connect(selfOut, (struct sockaddr *)&selfOut, sizeof(selfOut)) != SUCCESS){
        error("Initialize: Connection To Central Server Failed");
    }else{
        printf("Connected to central server\n");
    }

    // retrieve data from central server
    char buffer[BUFFER_MAX] = "Requesting List";
    int bytes = write(selfOut, buffer, strlen(buffer) + 1);

    bytes = read(selfOut, buffer, strlen(buffer));
    printf("\tReceived: %s\n", buffer);

    // process the buffer into a list
}

void peerConnect(){
  int i;
  for(i = 0; i < MAX_CLIENT; i++){
    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    inet_aton(onlineList[i].addr, &sock.sin_addr);
    sock.sin_port = htons(DEFAULT_PORT);
    if(connect(selfOut, (struct sockaddr *)&sock, sizeof(sock)) != SUCCESS){
      error("PeerConnect: Connect to peer clients failed");
    }else{
      printf("Connected to %s\n", onlineList[i].addr);
    }
  }
}

void listenIn(){
  // server listens and accepts connections
}
