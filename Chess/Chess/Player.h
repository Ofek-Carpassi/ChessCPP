#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "King.h"

class Player
{
private:
	char color;
	bool isInCheck;
	King* king;

public:
	Player(char color, King* king);

	~Player();

	King* getKing() const;

	bool getIsInCheck() const;

	void setIsInCheck(bool isInCheck);

	void setKing(King* king);
};

#endif