#pragma once
#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	Knight(std::string& pos, char colorAndType);

	~Knight();

	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board) const override;
};

#endif