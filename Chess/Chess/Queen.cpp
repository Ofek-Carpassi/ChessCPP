#include "Queen.h"

Queen::Queen(std::string& pos, char colorAndType)
{
	this->colorAndType = colorAndType;
	this->currentPos = pos;
}

Queen::Queen(char colorAndType)
{
	std::string pos;
	// Get the position from the color (black will be at the bottom, white at the top)
	if (colorAndType == 'Q')
	{
		pos = "d1";
	}
	else
	{
		pos = "d8";
	}

	this->colorAndType = colorAndType;
	this->currentPos = pos;
}

Queen::~Queen()
{
}

int Queen::isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const 
{
    // Get the position in terms of row and column in the array
    int currentRow = currentPos[1] - '1';
    int currentCol = currentPos[0] - 'a';
    int newRow = newPos[1] - '1';
    int newCol = newPos[0] - 'a';

    // If the destination is out of bounds (array is 8x8)
    if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) {
        return INVALID_MOVE_OUT_OF_BOUNDS;
    }

    // If the destination is the same as the current position
    if (currentPos == newPos) {
        return INVALID_MOVE_SAME_POS;
    }

	// If the move isn't a straight or diagonal move
    bool isStraightMove = currentRow == newRow || currentCol == newCol;
    bool isDiagonalMove = abs(newRow - currentRow) == abs(newCol - currentCol);
    if (!isStraightMove && !isDiagonalMove) {
        return INVALID_MOVE_ILLEGAL_MOVE;
    }

	// check what direction the queen is moving (up, down, left, right) and if it is diagonal
    int rowStep = (newRow == currentRow) ? 0 : (newRow > currentRow) ? 1 : -1;
    int colStep = (newCol == currentCol) ? 0 : (newCol > currentCol) ? 1 : -1;

	// iterate through the path to check if there are any pieces in the way
    int rowDistance = abs(newRow - currentRow);
    int colDistance = abs(newCol - currentCol);
    int maxDistance = (rowDistance > colDistance) ? rowDistance : colDistance;

    for (int i = 1; i < maxDistance; i++)
    {
		// Translate the position to a string (e.g. a1, b2, etc.)
        std::string pos = "";
        pos += (char)(currentCol + (i * colStep) + 'a');
        pos += (char)(currentRow + (i * rowStep) + '1');

		// If there is a piece in the way (not a null piece)
        if (board->getPiece(pos)->getColorAndType() != '#') 
        {
            return INVALID_MOVE_ILLEGAL_MOVE;
        }
    }

	// Check if the destination has a piece of the same color (if they do, the move is invalid)
    ChessPiece* destPiece = board->getPiece(newPos);
    bool isSameColor = (destPiece->getColorAndType() != '#' && (isupper(destPiece->getColorAndType()) == isupper(this->colorAndType)));
    if (isSameColor) {
        return INVALID_MOVE_PIECE_OF_PLAYER;
    }

    // Check if the move puts the player in check (invalid)
    // Save a temporary board and apply the move to it - then check if the player is in check
    Board tempBoard(*board);
    tempBoard.movePiece(currentRow, currentCol, newRow, newCol);
    char color = isupper(this->colorAndType) ? 'w' : 'b'; // Get the color of the piece (to know on which side to check for check)

    // Make sure we need to check for check (no need if we use this function for isInCheck)
    if (!isValidationCheck) {
        Board tempBoard(*board); // copy the board using the copy constructor
        // if the player is in check after the move, the move is invalid (pass true so we won't cause an infinite loop)
        if (game->isInCheck(color, &tempBoard, true))
        {
            return INVALID_MOVE_CAUSE_CHECK;
        }
    }

    // If the destination has a piece of the opposite color, the move is valid and the player can eat the piece
    return (destPiece->getColorAndType() != '#') ? VALID_MOVE_ATE_PIECE : SUCCESSFUL_MOVE;
}