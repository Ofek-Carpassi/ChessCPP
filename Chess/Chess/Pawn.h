#pragma once
#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	Pawn(std::string& pos, char colorAndType);

	~Pawn();

	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board) const override;
};

#endif