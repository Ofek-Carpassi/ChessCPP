#pragma once
#ifndef KING_H
#define KING_H

#include "ChessPiece.h"
#include "Board.h"

class King : public ChessPiece
{
public:
	King(char colorAndType);

	~King();

	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board) const override;
};

#endif