#include "Pawn.h"

Pawn::Pawn(std::string& pos, char colorAndType) : ChessPiece(pos, colorAndType)
{
}

Pawn::~Pawn()
{
}

int Pawn::isValidMove(std::string& currentPos, std::string& newPos, Board* board) const
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
	if (currentCol != newCol)
	{
		return 6;
	}


}

