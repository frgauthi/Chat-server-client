# Chat-server-client
A chat server and client that can talk to one another.

This code is intended to be an API in C++  that allows a simple client/server communication for chatting.

        multiple clients will be able to connect to the server. When a client sends a message to the server, 
    the server will relay that message to all other connected clients. I anticipate adding command parsing
    features to the server to allow for things like PM, and even small games that users can participate in.
    Eventually the message sent from server to client and vice versa will be encrypted using ssl.

        This code can be modified to fit your own needs and I will be expanding the functionality of the
    client and server regularly. If you find this code useful or end up using it for anything exciting, 
    please let me know! :) If you use the code, a link to https://github.com/frgauthi or reference to my
    name would be greatly appreciated! 


		Task			Command				Example
		-----------------	----------------------------	----------------------
		starting server		./server <port>			./server 9993
		connecting client	./client <IP Address> <port>	./client 127.0.0.1 9993


# Latest Update

	- Currently userNames are added to the buffer by the user, the server does not yet track usernames
	
	- Issue with the first message not being received by the server.
	
	- After user 1 sends a message user 2's first message is not received by the server but all messages
	after are received.
	
	- Issues connecting to the server over the internet, but using localhost or 127.0.0.1 works.
	The local network's IP also works to connect to the server. Ex (192.168.xxx.xxx)
