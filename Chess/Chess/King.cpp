#include "King.h"

King::King(char colorAndType)
{
	std::string pos;
	// Get the position from the color (black will be at the bottom, white at the top)
	if (colorAndType == 'K')
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

int King::isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const {
    int currentRow = currentPos[1] - '1';
    int currentCol = currentPos[0] - 'a';
    int newRow = newPos[1] - '1';
    int newCol = newPos[0] - 'a';

    // Basic validation checks
    if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) {
        return INVALID_MOVE_OUT_OF_BOUNDS;
    }

    if (currentPos == newPos) {
        return INVALID_MOVE_SAME_POS;
    }

    if (abs(newRow - currentRow) > 1 || abs(newCol - currentCol) > 1) {
        return INVALID_MOVE_ILLEGAL_MOVE;
    }

    ChessPiece* destPiece = board->getPiece(newPos);
    bool isSameColor = (destPiece->getColorAndType() != '0' && (isupper(destPiece->getColorAndType()) == isupper(this->colorAndType)));

    if (isSameColor) {
        return INVALID_MOVE_PIECE_OF_PLAYER;
    }

    // Create a temporary board to test the move
    Board tempBoard(*board);
    tempBoard.movePiece(currentRow, currentCol, newRow, newCol);

    // Check if move puts own king in check
    char color = isupper(this->colorAndType) ? 'w' : 'b';
    if (!isValidationCheck) {
        Board tempBoard(*board);
        if (game->isInCheck(color, &tempBoard, true)) {  // Pass true for validation check
            return INVALID_MOVE_CAUSE_CHECK;
        }
    }

    return (destPiece->getColorAndType() != '0') ? VALID_MOVE_ATE_PIECE : SUCCESSFUL_MOVE;
}