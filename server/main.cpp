#include "server.cpp"

void *sendMessage(chatServer *serv){
	printf("send message");
}

void *recMessage(){
	printf("recieve message");
}



int main(int argc, char *argv[]){
	
	if(argc <2){
		printf("ERROR no port provided\n");
		exit(1);
	}
	
	chatServer *testServer = new chatServer(atoi(argv[1]));
	
	
	while(true){
		testServer->readFromClient();
		testServer->writeToClient();
	}
			
	

	testServer->closeConnection();
}
