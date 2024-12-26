#pragma once
#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	Rook(std::string pos, char colorAndType);

	~Rook();

	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const override;
};

#endif