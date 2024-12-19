#pragma once
#ifndef NULLPIECE_H
#define NULLPIECE_H

#include "ChessPiece.h"

class NullPiece : public ChessPiece
{
public:
	NullPiece();

	~NullPiece();

	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board) const override;
};

#endif