// this is the main function for the client
// Author: Frank Gauthier

#include "client.cpp"

int main(int argc, char *argv[]){

	// create chatClient object pointer
	chatClient *testClient;	

	// initialize the test client with the given host and port
	testClient = new chatClient(atoi(argv[2]), gethostbyname(argv[1]));
	
	while(true){
		testClient->writeToServer();
		testClient->readFromServer();
	}

	testClient->closeConnection();
	return 0;	

}
