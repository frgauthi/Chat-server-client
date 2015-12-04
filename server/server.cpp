// functions file for the server class
// Author: Frank Gauthier

#include "server.h"


void chatServer::error(const char *msg)
{
        perror(msg);
        exit(1);
}



int chatServer::getLatestClientDesc(){
	return this->clientSockFileDesc;
}



void chatServer::openSocket(){
	serverSockFileDesc = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSockFileDesc < 0) error("Error opening socket!");
	else printf("Socket successfully opened..\n");
}



int chatServer::getServerSockFileDesc(){
	return this->serverSockFileDesc;
}



chatServer::chatServer(int port){
	
	this->openSocket();
	this->initServerAddress(port);
	this->bindSocket();
	this->portNumber = port;
	
}



void chatServer::initServerAddress(int port){
	bzero((char*) &server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(port);
}



void chatServer::bindSocket(){
	if(bind(serverSockFileDesc, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
	error("ERROR on binding!");
	else printf("Socket successfully bound...\n");
}



int chatServer::listenForClients(){
	listen(serverSockFileDesc, 5);
	clientSocketLength = sizeof(client_address);
	clientSockFileDesc = accept(serverSockFileDesc,
				 (struct sockaddr *) &client_address, &clientSocketLength);
	
	if(clientSockFileDesc < 0) error("ERROR accepting client");
	else{ 
		cout << "Client connected..." << endl;
		clientDescriptorList.push_back(clientSockFileDesc);
		numberOfClients++;
		
	}
	return clientSockFileDesc;
}


void chatServer::printClientDescriptors(){
	for(int i = 0; i<clientDescriptorList.size();i++){
		cout << clientDescriptorList[i] << endl;
	}
}


void chatServer::clearMessageBuffer(){
	bzero(messageBuffer, sizeof(messageBuffer));
}


void *chatServer::readFromClient(int clientDescriptor){
		clearMessageBuffer();
		loadBufferFromSocket(clientDescriptor);	
		if(strlen(messageBuffer) > 1){	
			printMessageBuffer();
		}
}

void chatServer::printMessageBuffer(){
	printf("%s", messageBuffer);
}

void chatServer::loadBufferFromSocket(int descriptor){
		n = read(descriptor, messageBuffer, MAX_MESSAGE_LENGTH);
		if( n < 0) error("Error reading from socket");
}

void chatServer::loadUserInputIntoBuffer(){
	fgets(messageBuffer, sizeof(messageBuffer), stdin);
}

void chatServer::writeBufferToSocket(int client){
		for(int i = 0; i < clientDescriptorList.size(); i++){
				if(client != clientDescriptorList[i]){
					n = write(clientDescriptorList[i], messageBuffer, strlen(messageBuffer));
					if(n < 0) error("ERROR writing to socket");
				}
		}
	
}

/*
void *chatServer::writeToClient(){
		
	readFromClient();
	writeBufferToSocket();
}*/



void chatServer::closeConnection(){
	close(clientSockFileDesc);
	close(serverSockFileDesc);
}






