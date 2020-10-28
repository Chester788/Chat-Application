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

	while (1)
	{
		std::cout << ".";
		SDL_Delay(200);

	}
	


	system("pause");
	return 0;
}