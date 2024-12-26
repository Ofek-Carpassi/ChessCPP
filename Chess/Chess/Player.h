#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "ChessPiece.h"

class ChessPiece;

class Player
{
private:
	char color;
	bool isInCheck;
	ChessPiece* king;

public:
	Player(char color, ChessPiece* king);

	~Player();

	ChessPiece* getKing() const;

	bool getIsInCheck() const;

	void setIsInCheck(bool isInCheck);

	void setKing(ChessPiece* king);
};

#endif