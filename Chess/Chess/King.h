#pragma once
#ifndef KING_H
#define KING_H

#include "ChessPiece.h"
#include "Board.h"
#include "MoveCase.h"
#include "Game.h"

class Board;

class Game;

class King : public ChessPiece
{
public:
	King(char colorAndType);

	~King();

	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const override;
};
#endif // KING_H