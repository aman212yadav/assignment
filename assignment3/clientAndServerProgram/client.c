#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main()
{
    int CreateSocket = 0,n = 0;
    char data[1024];
    struct sockaddr_in ipOfServer;

    memset(data, '0' ,sizeof(data));

    if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("Socket not created \n");
        return 1;
    }

    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(2020);
    ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer))<0)
    {
        printf("Some Error occured\n");
        return 1;
    }
    printf("client is running : Enter ur message for server-> ");
    gets(data);
    write(CreateSocket, data, strlen(data));
    memset(data,'\0',sizeof(data));
     read(CreateSocket, data, sizeof(data)-1);
     printf("message from server : %s\n",data);

    return 0;
}
