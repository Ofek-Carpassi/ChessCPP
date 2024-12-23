#include "King.h"

King::King(char colorAndType)
{
	std::string pos;
	// Get the position from the color (black will be at the bottom, white at the top)
	if (colorAndType == 'w')
	{
		pos = "e1";
	}
	else
	{
		pos = "e8";
	}

	this->currentPos = pos;
	this->colorAndType = colorAndType;
}

King::~King()
{
}

// NO NEED TO PASS CURRENT PLAYER BECAUSE THE GAME WILL HANDLE THAT AND ONLY CHECK IF MOVE IS VALID IF IT IS THE CURRENT PLAYER'S TURN

int King::isValidMove(std::string& currentPos, std::string& newPos, Board* board) const
{
	int currentRow = currentPos[1] - '0';
	int currentCol = currentPos[0] - 'a';

	int newRow = newPos[1] - '0';
	int newCol = newPos[0] - 'a';

	// Check for all 9 cases of returns
	// 0 if the move was successful
	// 1 - Valid move, ate a piece
	// 2 - invalid move - in the source pos there is no piece of the current player
	// 3 - invalid move - in the destination pos there is a piece of the current player
	// 4 - invalid move - the move will cause a check on the current player
	// 5 - invalid move - the indexes of the positions are out of bounds
	// 6 - invalid move - illegal move for the piece
	// 7 - invalid move - the source and destination positions are the same
	// 8 - valid move - checkmate - BONUS

	// Check if the new position is out of bounds
	if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7)
	{
		return 5;
	}

	// Check if the source and destination positions are the same
	if (currentPos == newPos)
	{
		return 7;
	}

	// Check if the move is legal
	if (abs(newRow - currentRow) > 1 || abs(newCol - currentCol) > 1)
	{
		return 6;
	}

	// Check if the destination position has a piece of the same color
	ChessPiece* piece = board->getPiece(newPos);
	char colorAndType = piece->getColorAndType();
	// Check if both of the characters are the same case (both upper or both lower)
	if (colorAndType != '0' && (colorAndType >= 'A' && colorAndType <= 'Z') == (this->getColorAndType() >= 'A' && this->getColorAndType() <= 'Z'))
	{
		return 3;
	}

	// Check if the move will cause a check on the current player
	// Not implemented

	// Check if the move is valid and if it ate a piece
	if (piece->getColorAndType() != '0')
	{
		return 1;
	}

	return 0;
}