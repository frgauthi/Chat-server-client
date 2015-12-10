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

void chatClient::printFileDescriptor(){
	printf("%d", clientSockFileDesc);
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

void chatClient::clearMessageBuffer(){
        bzero(messageBuffer, sizeof(messageBuffer));
}

void chatClient::loadUserInputIntoBuffer(){
	for(int i = 0; i<userName.size();i++) messageBuffer[i] = userName[i];
	messageBuffer[userName.size()] = ':';
	messageBuffer[userName.size() + 1] = ' ';
        fgets(messageBuffer+userName.size()+2, sizeof(messageBuffer)-userName.size()-3, stdin);
}

void chatClient::writeBufferToSocket(){
	n = write(clientSockFileDesc, messageBuffer, strlen(messageBuffer));
        if( n < 0 ) error("ERROR writing to socket");
}

void chatClient::loadBufferFromSocket(){
	n = read(clientSockFileDesc, messageBuffer, sizeof(messageBuffer)-1);
        if(n < 0) error("ERROR reading from socket");
}

void chatClient::writeToServer(){
        //cout << userName << ": ";
        clearMessageBuffer();
	loadUserInputIntoBuffer();
	if(strlen(messageBuffer) > 0){ 
		writeBufferToSocket();
		
	}
}

void chatClient::printMessageBuffer(){
	cout << messageBuffer;
}

void chatClient::readFromServer(){
        clearMessageBuffer();
        loadBufferFromSocket();
	printMessageBuffer();
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



void chatClient::promptForUserName(){
	string tmpName;
	cout << "Enter your alias: ";
	cin >> tmpName;
	this->userName = tmpName;
}
