#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_net.h>

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Error init SDL" << std::endl;
		system("pause");
		return 0;

	}

	if (SDLNet_Init() == -1)
	{
		std::cout << "Error init networking component" << std::endl;
		system("pause");
		return 0;
	}

	
	std::cout << "#########################################" << std::endl;
	std::cout << "Weclome! This is simple Chat Application" << std::endl;
	std::cout << "#########################################" << std::endl;

	std::cout << "Waiting for the chat!" << std::endl;

	IPaddress ip; // creating Ip address

	if (SDLNet_ResolveHost(&ip, "www.facebook.com", 80) == -1) ///Passing the ip address

	{
		std::cout << "Error connecting to website" << std::endl;
		system("pause");
		return 0;

	}
	
	///Creating/opening a socket using TCP connection and passing the ip address
	TCPsocket socket = SDLNet_TCP_Open(&ip);  ///TCP/UDP-type of connections
	
	if (!socket)
	{
		std::cout << "Error oppening socket for connection" << std::endl;
		system("pause");
		return 0;
	}

	else
	{
		std::string message = "GET /HTTPS/1.0\r\n\r\n"; //request to add HTML code from website
		
		int messageLenght = message.length() + 1;  //we add +1 for terminating null, we need length of message to send data

		if (SDLNet_TCP_Send(socket, message.c_str(), messageLenght) < messageLenght) //sending data with the socket, data and then lenght of the message
																					// If return value is less than length of messsage there will be an error

		{
			std::cout << "Error oppening socket for connection" << std::endl; 
		}

		else //If there is no error suppose to recieve message back
		{
			const int BUFFER_SIZE = 2000;

			char response[BUFFER_SIZE];

			if (SDLNet_TCP_Recv(socket, response, BUFFER_SIZE) <= 0) //recieve the socket that are opened, in response 
			{
				std::cout << "Error receiving message from the website" << std::endl;
			}

			else
			{
				std::cout << response << std::endl;
			}
		}
			//Once everything is finshed the socket has to be closed
		SDLNet_TCP_Close(socket);
	}
		//Closing tasks
		SDLNet_Quit();
		SDL_Quit();



	/*while (1)
	{
		std::cout << ".";
		SDL_Delay(200);

	}*/
	


	system("pause");
	return 0;
}