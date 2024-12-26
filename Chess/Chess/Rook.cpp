#include "Rook.h"

Rook::Rook(std::string pos, char colorAndType)
{
	this->currentPos = pos;
	this->colorAndType = colorAndType;
}

Rook::~Rook()
{
}

int Rook::isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const {
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

    // Rook moves only in straight lines
    if (currentRow != newRow && currentCol != newCol) {
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