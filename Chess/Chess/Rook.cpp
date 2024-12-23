#include "Rook.h"

Rook::Rook(std::string pos, char colorAndType)
{
	this->currentPos = pos;
	this->colorAndType = colorAndType;
}

Rook::~Rook()
{
}

int Rook::isValidMove(std::string& currentPos, std::string& newPos, Board* board) const
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

	// Check if the move is legal
	if (currentRow != newRow && currentCol != newCol)
	{
		return 6;
	}

	// Iterate over the rows
	if (currentRow != newRow)
	{
		for (int i = currentRow + 1; i < newRow; i++)
		{
			// Get the piece at the current position
			// Turn the col into a char
			char col = currentCol + 'a';
			std::string pos = std::string(1, col) + std::to_string(i);
			ChessPiece* piece = board->getPiece(pos);
			// Check if the piece is not empty
			if (piece->getColorAndType() != '0')
			{
				return 6;
			}
		}
		// Check the piece at the destination
		ChessPiece* piece = board->getPiece(newPos);
		// Check if the destination position has a piece of the same color
		char colorAndType = piece->getColorAndType();
		
		// Check if both the destination piece and current piece are the same color
		if (colorAndType != '0' && (colorAndType >= 'A' && colorAndType <= 'Z') == (this->getColorAndType() >= 'A' && this->getColorAndType() <= 'Z'))
		{
			return 3;
		}

		// Check if the move will cause a check on the current player (NOT IMPLEMENTED)

		// Check if the move is valid and if it ate a piece
		if (piece->getColorAndType() != '0')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	// Iterate over the columns
	if (currentCol != newCol)
	{
		for (int i = currentCol + 1; i < newCol; i++)
		{
			// Get the piece at the current position
			// Turn the col into a char
			char col = i + 'a';
			std::string pos = std::string(1, col) + std::to_string(newRow);
			ChessPiece* piece = board->getPiece(pos);
			// Check if the piece is not empty
			if (piece->getColorAndType() != '0')
			{
				return 6;
			}
		}
		// Check the piece at the destination
		ChessPiece* piece = board->getPiece(newPos);
		// Check if the destination position has a piece of the same color
		char colorAndType = piece->getColorAndType();

		// Check if both the destination piece and current piece are the smae color
		if (colorAndType != '0' && (colorAndType >= 'A' && colorAndType <= 'Z') == (this->getColorAndType() >= 'A' && this->getColorAndType() <= 'Z'))
		{
			return 3;
		}

		// Check if the move will cause a check on the current player (NOT IMPLEMENTED)

		// Check if the move is valid and if it ate a piece
		if (piece->getColorAndType() != '0')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	return 6;
}
