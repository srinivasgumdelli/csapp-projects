#define LINUX 1
#define WINDOWS 2

#ifdef __linux__
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <netdb.h>

    #define OSTYPE LINUX
#endif
#ifdef _WIN32 || _WIN64
    #include <winsock.h>
    #define OSTYPE WINDOWS
    // Compilation Not Working Yet
#endif

void error(char *msg){
    perror(msg);
    exit(1);
}

int main(){
    /*if(OSTYPE == WINDOWS){
        WSADATA wsaData; // if this doesn't work
        //WSAData wsaData; // then try this instead
       
        if(WSAStartup(MAKEWORD(2,0), &wsaData) != 0{
            fprintf(stderr, "WSAStartup failed.\n");
            exit(1);
        }
    } windows code */

   
    // IPv6 for IPv4 ::ffff:192.0.2.33 where 192.0.2.33 is the IPv4 address
    // HTTP = port 80, telnet = port 23, SMTP = port 25
    // Ports under 1024 are special, require special OS privileges to use

    // htons() host to network short, htonl() host to network to long
    // ntohs() network to host short, nohl() network to host long

    /* struct addrinfo{
        int ai_flags;         // AI_PASSIVE, AI_CANNONAME, etc.
        int ai_family;         // AF_INET, AF_INET6, AF_UNSPEC
        int ai_socktype;    // SOCK_STREAM, SOCK_DGRAM
        int ai_protocol;    // use 0 for "any"
        size_t ai_addrlen;    // size of ai_addr in bytes
        struct sockaddr *ai_addr; // struct sockaddr_in or _in6
        char *ai_cannonname;    // full canonical hostname
        struct addrinfo *ai_next; // linked list, next node
       } */
    /* struct sockaddr{
        unsigned short sa_family;    // address family, AF_xxx
        char sa_data[14];    // 14 bytes of protocl address
    } */

    /* getaddrinfo() fills out your struct addrinfo
       sa_data contains a destination address and port number for the socket
    */

  int sock, portno;
  struct sockaddr_in servAddress;
  struct hostent *server;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  portno = 5012;

  bzero((char*) &servAddress, sizeof(servAddress));
  servAddress.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
}