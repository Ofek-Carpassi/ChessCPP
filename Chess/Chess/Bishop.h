#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
	Bishop(std::string pos, char colorAndType);

	~Bishop();

	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const override;
};

#endif