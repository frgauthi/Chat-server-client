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

#define MAX_MESSAGE_LENGTH 256

class chatClient{

	private:
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
	
};

#endif
