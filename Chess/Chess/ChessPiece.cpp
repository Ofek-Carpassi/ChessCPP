#include "ChessPiece.h"

std::string ChessPiece::getCurrentPos() const
{
	return currentPos;
}

char ChessPiece::getColorAndType() const
{
	return colorAndType;
}

void ChessPiece::setPos(std::string& pos)
{
	currentPos = pos;
}