#pragma once
#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
	King(std::string& pos, char colorAndType);

	~King();

	virtual bool isValidMove(std::string& newPos) const override;
};

#endif