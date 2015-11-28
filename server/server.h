// this is a refactor of the server application
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


#define MAX_MESSAGE_LENGTH 256
#define MAX_THREADS 5


class chatServer{
	
	private:
	int serverSockFileDesc, clientSockFileDesc, portNumber;
	char messageBuffer[MAX_MESSAGE_LENGTH];
	socklen_t clientSocketLength;
	struct sockaddr_in server_address, client_address;
	int n;
	
	
	public:
	pthread_t threadId[MAX_THREADS];
	
	void error(const char *msg);
	void openSocket();
	int getServerSockFileDesc();
	explicit chatServer(int port);
	void initServerAddress(int port);
	void bindSocket();
	void listenForClients();
	void *readFromClient();		
	void *writeToClient();
	void closeConnection();
	
};


#endif
