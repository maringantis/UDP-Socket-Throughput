/*=== Assignment 1 ===

Author: Srinivasa Maringanti

Server side
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h> 
#include <sys/time.h>

void err(char *msg) // Method used to call errors
	{
		perror(msg);
		exit(1);
	}

int main(int argc, char *argv[])
	{
		int fd,nfd,comp;//fd and nfd will be used as a socket descriptor
		struct sockaddr_in server, client;
		int portnum=atoi(argv[1]);//Typecast 
		int bufsize=atoi(argv[2]);//Typecast 
		int sleeptime=atoi(argv[3]);//Typecast 
		char buf[bufsize];
		socklen_t c_len;

		if (argc < 2) 
				{
			       		fprintf(stderr,"[USAGE]: ./spdtestd <PORT> <BUFFER SIZE> <SLEEP TIME>\n");
			       		exit(0);
				}

// Creating socket and assigning socket descriptor

fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) // Try opening the socket
	{
    		err("[ERROR]: Opening socket");
	}

//Assigning the PORT IP and FAMILY
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr("10.250.4.34");//IP
		server.sin_port = htons(portnum);//Port
// Binding
	if (bind(fd, (struct sockaddr *) &server, sizeof(server)) < 0) 
	{
		err("[ERROR]: Binding");
	}
	while(1)
	{
		comp=recvfrom(fd, buf, bufsize, 0,(struct sockaddr *) &client, &c_len);//Recieving data
		if (comp < 0) 
			{
      				error("[ERROR]: Receiving issue");
			}
		printf("Seq # %d recieved! \n",buf[0]-'0');
		int i=buf[0]-'0';//Typecasting char from buf[0]
		usleep(sleeptime);

   		comp = sendto(fd,buf,bufsize,0, (struct sockaddr *) &client, c_len);//Sending ack for recv data
		if (comp < 0)
      		{	
		error("[ERROR]:  Sending issue");
		}
	}//while
		close(fd);
		exit(1);
}//main

		
