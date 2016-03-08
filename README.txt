=== UDP Socket ===

Author: Srinivasa Maringanti

== Description ==

*UDP program assignment uses udpclient.c and udpserver.c for running and execution.

== How to compile and run the files ==

------UDP code running and execution------

** After the code is ready first compile the files using make file that is already in the folder.
** Check for errors.Ignore warnings.If compiled the program is ready to run.
** Now on the server side of the terminal use the following command
	./udpserver 9207 1024 1
where 9207 is the port number which we are giving using command line argument,1024 is the bytes of message that has to be received and 1 is the sleeptime in milliseconds.
** Server starts running and is waiting for the client.
** Now on the client side of the terminal use the following command
	./udpclient 192.168.1.1 9207 8192
where 192.168.1.1 is the ip address which should be same as we hardcoded in the server,9207 is the port number which we are giving using command line argument and 1024 is the bytes of message that has to be transferred.
**As the server is already waiting, once client runs it accepts start recieving messages from the client and sends and acknowdgement back to the client.
**After 30 messages the total time taken and the throughput is printed onto the screen.
