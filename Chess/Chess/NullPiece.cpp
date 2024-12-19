#include "NullPiece.h"

NullPiece::NullPiece() : ChessPiece("0", '0') {}

NullPiece::~NullPiece() {}

int NullPiece::isValidMove(std::string& currentPos, std::string& newPos, Board* board) const
{
	return 6;
}