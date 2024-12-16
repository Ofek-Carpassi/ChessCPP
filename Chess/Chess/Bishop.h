#pragma once
#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
	Bishop(std::string& pos, char colorAndType);

	~Bishop();

	virtual bool isValidMove(std::string& newPos) const override;
};

#endif