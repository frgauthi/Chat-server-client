// these are the functions for the chat client
// Author: Frank Gauthier


#include "client.h"



void chatClient::error(const char *msg){
	perror(msg);
	exit(1);
}

chatClient::chatClient(int port, struct hostent *serv){
	setPortNumber(port);
	setServer(serv);
	openSocket();
	initServerAddress();
	connectToServer();
}

void chatClient::openSocket(){
	clientSockFileDesc = socket(AF_INET, SOCK_STREAM, 0);
        if(clientSockFileDesc < 0) error("ERROR opening client socket");
}

void chatClient::initServerAddress(){
        bzero((char*) &server_address, sizeof(server_address));
        server_address.sin_family = AF_INET;
        bcopy((char*) server->h_addr, (char*) &server_address.sin_addr.s_addr, server->h_length);
        server_address.sin_port = htons(portNumber);
}

void chatClient::connectToServer(){
        if(connect(clientSockFileDesc, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
        error("ERROR connecting to server");

}

void chatClient::writeToServer(){
        printf("client: ");
        bzero(messageBuffer, sizeof(messageBuffer));
        fgets(messageBuffer, sizeof(messageBuffer)-1, stdin);
        n = write(clientSockFileDesc, messageBuffer, strlen(messageBuffer));
        if( n < 0 ) error("ERROR writing to socket");
}

void chatClient::readFromServer(){
        bzero(messageBuffer, sizeof(messageBuffer));
        n = read(clientSockFileDesc, messageBuffer, sizeof(messageBuffer)-1);
        if(n < 0) error("ERROR reading from socket");
        printf("server: %s",messageBuffer);
}

void chatClient::closeConnection(){
        close(clientSockFileDesc);
}

void chatClient::setServer(struct hostent *serv){
	server = serv;
}

void chatClient::setPortNumber(int port){
	portNumber = port;
}
