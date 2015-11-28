// This is a refactoring of the chat client

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAX_MESSAGE_LENGTH 256

int clientSockFileDesc, portNumber, n;
struct sockaddr_in server_address;
struct hostent *server;
char messageBuffer[MAX_MESSAGE_LENGTH];


void error(const char *msg){
	perror(msg);
	exit(1);
}


void openSocket(){
	clientSockFileDesc = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSockFileDesc < 0) error("ERROR opening client socket");
	
}

void initServerAddress(){
	bzero((char*) &server_address, sizeof(server_address));
        server_address.sin_family = AF_INET;
        bcopy((char*) server->h_addr, (char*) &server_address.sin_addr.s_addr, server->h_length);
        server_address.sin_port = htons(portNumber);

}

void connectToServer(){
	if(connect(clientSockFileDesc, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
	error("ERROR connecting to server");
}

void writeToServer(){
	printf("Please enter the message: ");
	bzero(messageBuffer, sizeof(messageBuffer));
	fgets(messageBuffer, sizeof(messageBuffer)-1, stdin);
	n = write(clientSockFileDesc, messageBuffer, strlen(messageBuffer));
	if( n < 0 ) error("ERROR writing to socket");
}

void readFromServer(){
	bzero(messageBuffer, sizeof(messageBuffer));
	n = read(clientSockFileDesc, messageBuffer, sizeof(messageBuffer)-1);
	if(n < 0) error("ERROR reading from socket");
	printf("%s\n",messageBuffer);
}

void closeConnection(){
	close(clientSockFileDesc);
}




int main(int argc, char *argv[]){
	portNumber = atoi(argv[2]);
	server = gethostbyname(argv[1]);
	if(server == NULL){
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	openSocket();
	initServerAddress();
	connectToServer();
	writeToServer();
	readFromServer();
	closeConnection();
	return 0;
}
