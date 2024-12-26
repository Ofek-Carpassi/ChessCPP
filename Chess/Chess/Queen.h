#pragma once
#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	Queen(char colorAndType);

	~Queen();

	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const override;
};

#endif