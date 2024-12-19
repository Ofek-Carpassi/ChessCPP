#include "ChessPiece.h"

ChessPiece::ChessPiece(std::string pos, char colorAndType) : currentPos(pos), colorAndType(colorAndType)
{
}

ChessPiece::~ChessPiece()
{
}

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

int ChessPiece::isValidMove(std::string& currentPos, std::string& newPos, Board* board) const
{
	return -1;
}