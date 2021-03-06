#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_net.h>

const int PORT = 1234;
const int BUFFER_SIZE = 2000;

//Struct to store host addres and port number
IPaddress ip; // creating Ip address

//Short contstruction for chat(to send and receive messages from client and server) (For making a class later)
bool ChatIsOpen = true;
bool DeliverMessage = true;
char SendMessage[BUFFER_SIZE] = { '\0' };
//we add +1 for terminating null, we need length of message to send data
std::string Message;
int messageLenght = Message.length() + 1;



//socket to transfer/connecting data to server
TCPsocket Socket = nullptr;


int main(int argc, char* argv[])
{
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

	/////========Code specific for client=======//////

	if (SDLNet_ResolveHost(&ip, "localHost", PORT) == -1) ///Passing the ip address, can use 127.0.0.1

	{
		std::cout << "Error creating a client!" << std::endl;
		system("pause");
		return 0;

	}

	///Creating/opening a socket using TCP connection and passing the ip address
	Socket = SDLNet_TCP_Open(&ip);  ///TCP/UDP-type of connections

	if (!Socket)
	{
		std::cout << "Error oppening socket for connection!" << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "Connected to server!" << std::endl;
	system("pause");

	system("cls");
	std::cout << "#########################################" << std::endl;
	std::cout << "Weclome! This is simple Chat Application!" << std::endl;
	std::cout << "#########################################" << std::endl;
	std::cout << "Waiting for the chat!" << std::endl;

	//String received message
	char message[BUFFER_SIZE];

	//Receive message from server with While Loop
	while (ChatIsOpen)
	{

		if (DeliverMessage)
		{

			if (SDLNet_TCP_Recv(Socket, message, BUFFER_SIZE) <= 0) //sending data with the client socket, data and then lenght of the message
																	// If return value is less than length of messsage there will be an error

			{
				std::cout << "Error receiving message!" << std::endl;
			}


			else
			{
				std::cout << message << std::endl;
				DeliverMessage = false;
				system("pause");

			}
		}

				else
				{
					std::cout << "Send your message:";
					std::getline(std::cin, Message);
					if (SDLNet_TCP_Send(Socket, Message.c_str(), messageLenght) < messageLenght)
					{
						std::cout << "Error sending message to server!" << std::endl;
						system("pause");
					}

					else
					{
						
						std::cout << "Message sent to server" << std::endl;
						system("pause");
						Message.clear();
						DeliverMessage = true;
					}

				}
	}
	


	//Once everything is finshed the socket has to be closed
	SDLNet_TCP_Close(Socket);

	//Closing tasks
	SDLNet_Quit();
	SDL_Quit();



	system("pause");
	return 0;
}