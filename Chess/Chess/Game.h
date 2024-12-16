#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>
#include "Board.h"
#include "Player.h"

class Game
{
private:
	char currentPlayer;
	Player* whitePlayer;
	Player* blackPlayer;
	Board* board;
	std::string startPos;

public:
	Game(char currentPlayer);

	~Game();

	void startGame();

	void isInCheck();

	std::string initStartPos();
};

#endif