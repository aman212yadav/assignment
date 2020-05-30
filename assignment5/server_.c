#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<stdio.h>

#include<stdlib.h>

#include<sys/socket.h>

#include<netinet/in.h>

#include<string.h>

#include <arpa/inet.h>

#include <fcntl.h> // for open

#include <unistd.h> // for close

#include<pthread.h>
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
char data[1025];
void * socketThread(void *arg)

{

  int clintConnt = *((int *)arg);

  read(clintConnt, data, sizeof(data)-1);
  printf("server : one client sent me a message and the message is -> %s \n",data);
  printf("server : enter response message for client -> ");

  // Send message to the client socket

  pthread_mutex_lock(&lock);
  gets(data);
  pthread_mutex_unlock(&lock);

   write(clintConnt, data, strlen(data));
   printf("server: response message sent to the client\n");
   printf("Exit socketThread \n");

  close(clintConnt);

}

int main()
{


	int sock = 0, clintConnt = 0;
	struct sockaddr_in ipOfServer;
	sock = socket(AF_INET, SOCK_STREAM, 0); // creating socket
	memset(&ipOfServer, '0', sizeof(ipOfServer));
	memset(data, '\0', sizeof(data));
	ipOfServer.sin_family = AF_INET;
	ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
	ipOfServer.sin_port = htons(2020);
	bind(sock, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));
	listen(sock , 3);
	 pthread_t tid[60];
	 int i=0;
     printf("\nserver is Running.\n");
	while(1)
	{

		clintConnt = accept(sock, (struct sockaddr*)NULL, NULL);
		pthread_create(&tid[i], NULL, socketThread, &clintConnt);
		i++;

     }

     return 0;
}
