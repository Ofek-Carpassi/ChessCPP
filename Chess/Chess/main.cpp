#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Game.h"

int main()
{
	Game game = Game();

	srand(time_t(NULL));


	Pipe p;
	bool isConnect = p.connect();

	std::string ans;
	while (!isConnect)
	{
		std::cout << "cant connect to graphics" << std::endl;
		std::cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << std::endl;
		std::cin >> ans;

		if (ans == "0")
		{
			std::cout << "trying connect again.." << std::endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return 0;
		}
	}


	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr1"); // just example...

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	std::string msgFromGraphics;

	do
	{
		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();

		std::string Code = game.checkMove(msgFromGraphics);

		// YOUR CODE
		strcpy_s(msgToGraphics, Code.c_str());

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

	} while (msgFromGraphics != "quit");

	p.close();
	game.~Game();

	return 0;
}
