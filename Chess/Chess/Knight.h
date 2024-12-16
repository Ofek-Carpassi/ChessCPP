#pragma once
#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	Knight(std::string& pos, char colorAndType);

	~Knight();

	virtual bool isValidMove(std::string& newPos) const override;
};

#endif