#include "Game.h"

Game::Game()
{
	this->currentPlayer = 'w';
	this->board = new Board();

	std::string kingPos = "e1";
	ChessPiece* king = this->board->getPiece(kingPos);
	this->whitePlayer = new Player('w', king);
	
	kingPos = "e8";
	king = this->board->getPiece(kingPos);
	this->blackPlayer = new Player('b', king);

	this->startPos = initStartPos();
	this->isInPlay = false;
}

Game::~Game()
{
	delete this->board;
	delete this->whitePlayer;
	delete this->blackPlayer;
}

void Game::startGame()
{
	this->isInPlay = true;

	while (isInPlay)
	{

	}
}

void Game::isInCheck()
{
}

std::string Game::initStartPos()
{
	std::string pos = "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr0";
	return pos;
}