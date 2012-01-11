#include "servant.h"

int main(){
}

void error(const char *msg){
  perror(msg);
  exit(EXIT_FAILURE);
}

void bootUp(){
  if((selfSock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    error("BootUp: Socket creation failed");
  }

  struct sockaddr_in selfAddr;
  memset(&selfAddr, 0, sizeof(selfAddr));
  selfAddr.sin_family = AF_INET;
  selfAddr.sin_addr.s_addr = INADDR_ANY;
  selfAddr.sin_port = htons(DEFAULT_PORT);
  int socklen = sizeof(sock);
  if(bind(selfSock, (struct sockaddr *)&sock, socklen) == -1){
    error("BootUp: Binding failed");
  }
}

void initialize(){
}
