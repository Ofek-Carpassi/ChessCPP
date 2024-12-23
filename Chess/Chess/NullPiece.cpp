#include "NullPiece.h"

NullPiece::NullPiece(std::string pos)
{
	this->currentPos = pos;
	this->colorAndType = '0';
}

NullPiece::~NullPiece() {}

int NullPiece::isValidMove(std::string& currentPos, std::string& newPos, Board* board) const
{
	return 6;
}