#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_net.h>

const int PORT = 1234;
//message to send to clients
std::string message;

//Struct to store host addres and port number
IPaddress ip; // creating Ip address

//socket for incoming/listening connections
TCPsocket listenSocket = nullptr;

//socket to transfer/connecting data to client
TCPsocket clientSocket = nullptr;

int main(int argc, char* argv[])
{

	///Intialising
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Error init SDL!" << std::endl;
		system("pause");
		return 0;

	}

	if (SDLNet_Init() == -1)
	{
		std::cout << "Error init networking component!" << std::endl;
		system("pause");
		return 0;
	}

	/////========Code specific for server=======//////

	if (SDLNet_ResolveHost(&ip, nullptr, PORT) == -1) ///Passing the ip address

	{
		std::cout << "Error creating a server!" << std::endl;
		system("pause");
		return 0;

	}
	
	///Creating/opening a socket using TCP connection and passing the ip address
	listenSocket = SDLNet_TCP_Open(&ip);  ///TCP/UDP-type of connections
	if (!listenSocket)
	{
		std::cout << "Error oppening socket for connection!" << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "Server is waiting for clients to connect!" << std::endl;

	while (!clientSocket) //Breaks the lopp when the client is connecting
	{
		clientSocket = SDLNet_TCP_Accept(listenSocket);
		std::cout << "."; //Represent waiting for the client to connect
		SDL_Delay(500);
	}
		
	SDLNet_TCP_Close(listenSocket);
	std::cout << "Client connected!" << std::endl;
	system("pause");

	system("cls");
	std::cout << "#########################################" << std::endl;
	std::cout << "Weclome! This is simple Chat Application!" << std::endl;
	std::cout << "#########################################" << std::endl;
	std::cout << "Waiting for the chat!" << std::endl;

	//Create a message for the client
	message = "Welcome to the chat!";

	//we add +1 for terminating null, we need length of message to send data
	int messageLenght = message.length() + 1;  

	if (SDLNet_TCP_Send(clientSocket, message.c_str(), messageLenght) < messageLenght) //sending data with the client socket, data and then lenght of the message
																						// If return value is less than length of messsage there will be an error

		{
			std::cout << "Error sending message to client!" << std::endl;
		}

	
		else
		{
			std::cout << "Message sent to client!" << std::endl;
		}
	
	//Once everything is finshed the socket has to be closed
	SDLNet_TCP_Close(clientSocket);




		
		//Closing tasks
		SDLNet_Quit();
		SDL_Quit();



	
	


	system("pause");
	return 0;
}