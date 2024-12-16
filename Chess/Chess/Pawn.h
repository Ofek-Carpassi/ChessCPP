#pragma once
#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	Pawn(std::string& pos, char colorAndType);

	~Pawn();

	virtual bool isValidMove(std::string& newPos) const override;
};

#endif