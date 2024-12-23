#include "Bishop.h"

Bishop::Bishop(std::string pos, char colorAndType)
{
	this->currentPos = pos;
	this->colorAndType = colorAndType;
}

Bishop::~Bishop()
{
}

int Bishop::isValidMove(std::string& currentPos, std::string& newPos, Board* board) const
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
	if (abs(newRow - currentRow) != abs(newCol - currentCol))
	{
		return 6;
	}

	// Check if the path is clear
	if (newRow > currentRow && newCol > currentCol)
	{
		for (int i = 1; i < abs(newRow - currentRow); i++)
		{
			char col = currentCol + i + 'a';
			std::string pos = std::string(1, col) + std::to_string(currentRow + i);
			ChessPiece* piece = board->getPiece(pos);
			if (piece->getColorAndType() != '0')
			{
				return 6;
			}
		}
		ChessPiece* piece = board->getPiece(newPos);
		if (piece->getColorAndType() != '0' && (piece->getColorAndType() >= 'A' && piece->getColorAndType() <= 'Z') == (this->getColorAndType() >= 'A' && this->getColorAndType() <= 'Z'))
		{
			return 3;
		}

		if (piece->getColorAndType() != '0')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	if (newRow > currentRow && newCol < currentCol)
	{
		for (int i = 1; i < abs(newRow - currentRow); i++)
		{
			char col = currentCol - i + 'a';
			std::string pos = std::string(1, col) + std::to_string(currentRow + i);
			ChessPiece* piece = board->getPiece(pos);
			if (piece->getColorAndType() != '0')
			{
				return 6;
			}
		}
		ChessPiece* piece = board->getPiece(newPos);
		if (piece->getColorAndType() != '0' && (piece->getColorAndType() >= 'A' && piece->getColorAndType() <= 'Z') == (this->getColorAndType() >= 'A' && this->getColorAndType() <= 'Z'))
		{
			return 3;
		}

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