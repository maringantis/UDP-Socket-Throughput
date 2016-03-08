/*=== Assignment 1 ===

Author: Srinivasa Maringanti
Client side
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>  
#include <sys/time.h>
#define BILLION 1E9

void err(char *msg) // Method used to call errors
	{
		perror(msg);
		exit(0);
	}

int main(int argc, char *argv[])
	{
		int fd,portnum,comp;//fd and nfd will be used as a socket descriptor
		struct sockaddr_in server;
		struct timespec ts,te;
		socklen_t s_len;
		int bufsize=atoi(argv[3]);
		char buf[bufsize];
		portnum=atoi(argv[2]);

//Prompt the Usage of the input if wrong
	if (argc < 3) 
	{
	       fprintf(stderr,"[USAGE]:./spdtest.c <IP> <PORT> <BUFFER SIZE>\n");
	       exit(1);
	}

// Create a socket and check for error if any

	fd = socket(AF_INET, SOCK_DGRAM, 0);
    		if (fd < 0) 
        		{
			err("[ERROR]: Opening socket");
			}
//Assigning the PORT IP and FAMILY
	server.sin_family = AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);// IP
	server.sin_port=htons(portnum);//PORT

	memset(buf,'4',bufsize);// Setting all the buffer with memset
	int i=1;
	double grandtotal=0;
	for(i;i<=30;i++)
		{//Creating the sequence number for 30 msgs
		int temp2=0;
		char temp1;
		temp1=buf[0];//4
		temp2=temp1-'0';//52 //Typecast 
         	temp2=i;//4
		buf[0]=temp2+'0';//Typecast 
		s_len=sizeof(server);
		double strtclk=clock_gettime(CLOCK_REALTIME,&ts);//Starting the clock
		//Sending data
  		comp = sendto(fd, buf, strlen(buf), 0, &server, s_len);
     		if (comp < 0)
      		{	
		error("[ERROR]:  Sending issue");
		}
		//Recieving ack of sent data
		comp = recvfrom(fd, buf,strlen(buf),0,&server, &s_len);
    		if (comp < 0) 
		{
      		error("[ERROR]: Receiving issue");
		}
   		printf("Ack of Seq #: %d recieved \n", buf[0]-'0');
		double stpclk=clock_gettime(CLOCK_REALTIME,&te);//Ending the clock
		double duration1= ((te.tv_sec-ts.tv_sec)*BILLION)+(te.tv_nsec-ts.tv_nsec);//Calculating time in nanoseconds;
		duration1= duration1/BILLION;//Converting nanosecs to seconds
		printf("Total Time for seq %d #: %lf \n",buf[0]-'0',duration1);
		grandtotal= grandtotal+duration1;//Calculating total time

		}
	printf("Total time for 30 msg in seconds: %lf \n",grandtotal);
	double throughput= 30*(float)bufsize/grandtotal;
	printf("Throughput for 30 msg: %lf \n",throughput);
  close(fd);
   exit(1);
}
