// this is the header file for the server application
// Author: Frank Gauthier

#ifndef chatServer_h
#define chatServer_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <string>


#define MAX_MESSAGE_LENGTH 256


using namespace std;

class chatServer{
	
	private:
	int serverSockFileDesc, clientSockFileDesc, portNumber;
	char messageBuffer[MAX_MESSAGE_LENGTH];
	socklen_t clientSocketLength;
	struct sockaddr_in server_address, client_address;
	int n, currentThreads, numberOfClients;
	vector<pthread_t> threadList;
	vector<int> clientDescriptorList;
	
	public:
	

	void error(const char *msg);
	void openSocket();
	int getServerSockFileDesc();
	explicit chatServer(int port);
	void initServerAddress(int port);
	void bindSocket();
	int listenForClients();
	void *readFromClient(int);		
	void *writeToClient();
	void closeConnection();
	void clearMessageBuffer();
	void loadBufferFromSocket(int);
	void printMessageBuffer();
	void loadUserInputIntoBuffer();
	void writeBufferToSocket(int);
	void printClientDescriptors();	
	int getLatestClientDesc();
};


#endif
