#include "Queen.h"

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

	// set the king pos using chess piece setPos func
	this->colorAndType = colorAndType;
	this->currentPos = pos;
}

Queen::~Queen()
{
}

int Queen::isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const {
    int currentRow = currentPos[1] - '1';
    int currentCol = currentPos[0] - 'a';
    int newRow = newPos[1] - '1';
    int newCol = newPos[0] - 'a';

    if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) {
        return INVALID_MOVE_OUT_OF_BOUNDS;
    }

    if (currentPos == newPos) {
        return INVALID_MOVE_SAME_POS;
    }

    // Queen moves either like a rook (straight) or bishop (diagonal)
    bool isStraightMove = currentRow == newRow || currentCol == newCol;
    bool isDiagonalMove = abs(newRow - currentRow) == abs(newCol - currentCol);

    if (!isStraightMove && !isDiagonalMove) {
        return INVALID_MOVE_ILLEGAL_MOVE;
    }

    // Check path
    int rowStep = (newRow == currentRow) ? 0 : (newRow > currentRow) ? 1 : -1;
    int colStep = (newCol == currentCol) ? 0 : (newCol > currentCol) ? 1 : -1;

    for (int i = 1; i < std::max(abs(newRow - currentRow), abs(newCol - currentCol)); i++) {
        std::string pos = "";
        pos += (char)(currentCol + (i * colStep) + 'a');
        pos += (char)(currentRow + (i * rowStep) + '1');
        if (board->getPiece(pos)->getColorAndType() != '0') {
            return INVALID_MOVE_ILLEGAL_MOVE;
        }
    }

    ChessPiece* destPiece = board->getPiece(newPos);
    bool isSameColor = (destPiece->getColorAndType() != '0' &&
        (isupper(destPiece->getColorAndType()) == isupper(this->colorAndType)));

    if (isSameColor) {
        return INVALID_MOVE_PIECE_OF_PLAYER;
    }

    // Check validation
    Board tempBoard(*board);
    tempBoard.movePiece(currentRow, currentCol, newRow, newCol);
    char color = isupper(this->colorAndType) ? 'w' : 'b';
    if (!isValidationCheck) {
        Board tempBoard(*board);
        if (game->isInCheck(color, &tempBoard, true)) {  // Pass true for validation check
            return INVALID_MOVE_CAUSE_CHECK;
        }
    }

    return (destPiece->getColorAndType() != '0') ? VALID_MOVE_ATE_PIECE : SUCCESSFUL_MOVE;
}