///////////////////////////////////////////////////////
// This is the server class for the chat application //
//////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/////////////////////////
// function prototypes //
/////////////////////////

void checkArgs();
void getPortFromArgs();
void openSocket();
void bindSocket();
void initServerAddress();
void listenForClients();
void initServer();
void readFromClient();
void writeToClient();
void closeConnection();
int main(int argc, char *argv[]);

        int sockfd, newsockfd, portno;
        char msgBuffer[256];
        socklen_t clientSocketLength;
        struct sockaddr_in server_address, client_address;
        int n;



///////////////////////////////////////////////
// functions for the soon to be Server class //
///////////////////////////////////////////////

void error(const char *msg)
{
	perror(msg);
	exit(1);
}



void openSocket(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) error("ERROR opening socket");
}



void bindSocket(){
	if(bind(sockfd,(struct sockaddr *) &server_address, sizeof(server_address)) < 0)
	error("ERROR on binding");
}




void initServerAddress(){
	
	bzero((char*) &server_address, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(portno);

}



void listenForClients(){
	listen(sockfd, 5);
	clientSocketLength = sizeof(client_address);
	newsockfd = accept(sockfd, (struct sockaddr *) &client_address, &clientSocketLength);
	if(newsockfd < 0) error("ERROR on accept");
}



void initServer(){
	openSocket();
	initServerAddress();	
	bindSocket();
	
}



void readFromClient(){
	bzero(msgBuffer, 256);
	n = read(newsockfd, msgBuffer, 255);
	if(n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n", msgBuffer);
}



void writeToClient(){
	
	n = write(newsockfd, "I got your message", 18);
	if(n < 0) error("ERROR writing to socket");
}



void closeConnection(){
	close(newsockfd);
	close(sockfd);
}




int main(int argc, char *argv[]){
	if(argc < 2){
		error("ERROR no port provided");
		exit(1);
	}
	portno = atoi(argv[1]);
	
	initServer();
	listenForClients();	
	readFromClient();
	writeToClient();
	closeConnection();
	return 0;
	
}
