#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char msg){
  perror(msg);
  exit(0);
}

int main(){
  char *servAddress = "127.0.0.1";
}
