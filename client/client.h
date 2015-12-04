// This is the header file for the chat client application.
// Author: Frank Gauthier

#ifndef client_h
#define client_h


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <pthread.h>

#define MAX_MESSAGE_LENGTH 256
#define MAX_NAME_SIZE 15

using namespace std;


class chatClient{

	private:
	string userName;
	int clientSockFileDesc, portNumber, n;
	struct sockaddr_in server_address;
	struct hostent *server;
	char messageBuffer[MAX_MESSAGE_LENGTH];
	
	public:
	explicit chatClient(int, struct hostent *);
	void error(const char *);
	void openSocket();
	void initServerAddress();
	void connectToServer();
	void writeToServer();
	void readFromServer();
	void closeConnection();
	void setPortNumber(int port);
	void setServer(struct hostent *);
	void printFileDescriptor();
	void clearMessageBuffer();
	void loadUserInputIntoBuffer();
	void writeBufferToSocket();
	void loadBufferFromSocket();
	void printMessageBuffer();
	void setUserName(string*);
	void promptForUserName();	
};

#endif
