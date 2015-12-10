// this is the main function for the client
// Author: Frank Gauthier

#include "client.cpp"
pthread_t threadID[10];
int clientCount = 0;
void *sendMessage(void *serv){
	chatClient *tmpClient = (chatClient*)serv;
	while(true){
		tmpClient->writeToServer();
	}
}

void *recMessage(void *serv){
	chatClient *tmpClient = (chatClient*)serv;
	while(true){
		tmpClient->readFromServer();
	}
}

int main(int argc, char *argv[]){
	
	

	// create chatClient object pointer
	chatClient *testClient;	
	
	// initialize the test client with the given host and port
	testClient = new chatClient(atoi(argv[2]), gethostbyname(argv[1]));
	
	testClient->promptForUserName();
	
	
	pthread_create(&threadID[1], NULL, recMessage, (void*) testClient );
	pthread_create(&threadID[2], NULL, sendMessage, (void*) testClient );
	
	pthread_join(threadID[2],NULL);
	
	testClient->closeConnection();
	return 0;	

}
