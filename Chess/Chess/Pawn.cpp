#include "Pawn.h"

Pawn::Pawn(std::string& pos, char colorAndType)
{
	this->currentPos = pos;
	this->colorAndType = colorAndType;
}

Pawn::~Pawn()
{
}

int Pawn::isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const {
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

    // Determine direction based on color (white moves up, black moves down)
    int direction = isupper(colorAndType) ? 1 : -1;

    // Regular one square forward move
    if (newCol == currentCol && newRow == currentRow + direction) {
        if (board->getPiece(newPos)->getColorAndType() != '0') {
            return INVALID_MOVE_ILLEGAL_MOVE;
        }
        return SUCCESSFUL_MOVE;
    }

    // Initial two square move
    bool isInitialPosition = (isupper(colorAndType) && currentRow == 1) ||
        (!isupper(colorAndType) && currentRow == 6);
    if (isInitialPosition && newCol == currentCol && newRow == currentRow + (2 * direction)) {
        // Check if path is clear
        std::string midPos = "";
        midPos += currentPos[0];
        midPos += (char)(currentRow + direction + '1');
        if (board->getPiece(midPos)->getColorAndType() != '0' ||
            board->getPiece(newPos)->getColorAndType() != '0') {
            return INVALID_MOVE_ILLEGAL_MOVE;
        }
        return SUCCESSFUL_MOVE;
    }

    // Diagonal capture
    if (abs(newCol - currentCol) == 1 && newRow == currentRow + direction) {
        ChessPiece* destPiece = board->getPiece(newPos);
        if (destPiece->getColorAndType() == '0') {
            return INVALID_MOVE_ILLEGAL_MOVE;
        }
        bool isSameColor = (isupper(destPiece->getColorAndType()) == isupper(this->colorAndType));
        if (isSameColor) {
            return INVALID_MOVE_PIECE_OF_PLAYER;
        }
        return VALID_MOVE_ATE_PIECE;
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

    return INVALID_MOVE_ILLEGAL_MOVE;
}