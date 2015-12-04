//this is the main function for the server
// Author: Frank Gauthier

#include "server.cpp"

void *sendMessage(chatServer *serv){
	printf("send message");
}

void *recMessage(void *serv){
	chatServer *tmpServer = (chatServer*) serv;
	int client = tmpServer->getLatestClientDesc();
	while(true) {
			tmpServer->readFromClient(client);
			//tmpServer->printClientDescriptors();
			tmpServer->writeBufferToSocket(client);
	}
}



int main(int argc, char *argv[]){
	

	pthread_t threadID[4];
	int clientCount = 0;

	if(argc <2){
		printf("ERROR no port provided\n");
		exit(1);
	}
	
	chatServer *testServer = new chatServer(atoi(argv[1]));
	
	
	while(clientCount < 4)
	{	
	
		testServer->listenForClients();
		pthread_create(&threadID[clientCount++],NULL,recMessage, (void *) testServer);
	
	}

	testServer->closeConnection();
}
