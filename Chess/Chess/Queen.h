#pragma once
#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	Queen(std::string& pos, char colorAndType);

	~Queen();

	virtual bool isValidMove(std::string& newPos) const override;
};

#endif