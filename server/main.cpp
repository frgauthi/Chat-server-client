//this is the main function for the server
// Author: Frank Gauthier

#include "server.cpp"

void *sendMessage(chatServer *serv){
	printf("send message");
}

void *recMessage(void *serv){
	chatServer *tmpServer = (chatServer*) serv;
	while(true) tmpServer->readFromClient();
}



int main(int argc, char *argv[]){
	
//	struct timeval tv;
//	fd_set readfds;

//	tv.tv_sec = 2;
//	tv.tv_usec = 500000;

//	FD_ZERO(&readfds);
//	FD_SET(0, &readfds);
	pthread_t threadID[4];
	int clientCount = 0;

	if(argc <2){
		printf("ERROR no port provided\n");
		exit(1);
	}
	
	chatServer *testServer = new chatServer(atoi(argv[1]));
	
	
	while(clientCount < 4)
	{	
//		select(1, &readfds, NULL, NULL, &tv);		
//		if(FD_ISSET(0, &readfds))printf("A key was pressed!");
//		else printf("Timed out.");
	
		testServer->listenForClients();
		pthread_create(&threadID[clientCount++],NULL,recMessage, (void *) testServer);
		
		
		//testServer->readFromClient();
		//testServer->writeToClient();
	
	}
			
	

	testServer->closeConnection();
}
