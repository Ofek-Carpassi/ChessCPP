#pragma once
#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	Rook(std::string& pos, char colorAndType);

	~Rook();

	virtual bool isValidMove(std::string& newPos) const override;
};

#endif