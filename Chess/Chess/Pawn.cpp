#include "Pawn.h"

Pawn::Pawn(std::string& pos, char colorAndType)
{
	this->currentPos = pos;
	this->colorAndType = colorAndType;
}

Pawn::~Pawn()
{
}

int Pawn::isValidMove(std::string& currentPos, std::string& newPos, Board* board) const
{
	int currentRow = currentPos[1] - '1';
	int currentCol = currentPos[0] - 'a';

	int newRow = newPos[1] - '1';
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

	// if he didn't move forward and didn't move in a diagonal one square
	if (abs(newRow - currentRow) == 1 && abs(newCol - currentCol) == 1 && board->getPiece(newPos)->getColorAndType() == '0')
	{
		return 6;
	}
	else if (abs(newRow - currentRow) == 1 && abs(newCol - currentCol) == 1 && board->getPiece(newPos)->getColorAndType() != '0')
	{
		return 1;
	}	
	else if (abs(newRow - currentRow) == 1 && abs(newCol - currentCol) == 0 && board->getPiece(newPos)->getColorAndType() == '0')
	{
		return 0;
	}
	else if (abs(newRow - currentRow) == 1 && abs(newCol - currentCol) == 0 && board->getPiece(newPos)->getColorAndType() != '0')
	{
		return 6;
	}
	else if (abs(newRow - currentRow) == 2 && abs(newCol - currentCol) == 0 && board->getPiece(newPos)->getColorAndType() == '0')
	{
		if (colorAndType == 'P' && currentRow == 1)
		{
			// Check if there is a piece in the way
			std::string pos = "";
			// Get the piece between newPos and currentPos
			pos += currentPos[0];
			pos += (char)(currentRow + 1 + '0');
			if (board->getPiece(pos)->getColorAndType() != '0')
			{
				return 6;
			}
			else
			{
				return 0;
			}
		}
		else if (colorAndType == 'p' && currentRow == 6)
		{
			// Check if there is a piece in the way
			std::string pos = "";
			// Get the piece between newPos and currentPos
			pos += currentPos[0];
			pos += (char)(currentRow - 1 + '0');
			if (board->getPiece(pos)->getColorAndType() != '0')
			{
				return 6;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 6;
		}
	}
	else
	{
		return 6;
	}
}