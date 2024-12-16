#pragma once
#ifndef NULLPIECE_H
#define NULLPIECE_H

#include "ChessPiece.h"

class NullPiece : public ChessPiece
{
public:
	NullPiece();

	~NullPiece();

	virtual bool isValidMove(std::string& newPos) const override;
};

#endif