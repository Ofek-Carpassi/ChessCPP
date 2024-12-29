#include "NullPiece.h"

NullPiece::NullPiece(std::string pos)
{
	this->currentPos = pos;
	this->colorAndType = '#';
}

NullPiece::~NullPiece() {}

int NullPiece::isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const
{
	return 6;
}