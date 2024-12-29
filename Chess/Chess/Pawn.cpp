#include "Pawn.h"

Pawn::Pawn(std::string& pos, char colorAndType)
{
	this->currentPos = pos;
	this->colorAndType = colorAndType;
}

Pawn::~Pawn()
{
}

int Pawn::isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const
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

    // Determine direction based on color (white moves up, black moves down)
    int direction = isupper(colorAndType) ? 1 : -1;

    // If the pawn moves forward one square
    if (newCol == currentCol && newRow == currentRow + direction) {
        // Check if path is clear
        if (board->getPiece(newPos)->getColorAndType() != '#') {  // Empty square is '#'
            return INVALID_MOVE_ILLEGAL_MOVE;
        }
        // Check if the pawn is at the end of the board (promotion)
        if ((isupper(colorAndType) && newRow == 7) || (!isupper(colorAndType) && newRow == 0)) {
            return VALID_MOVE_PROMOTION;
        }
        return SUCCESSFUL_MOVE;
    }

    // If the pawn is at its initial position
    bool isInitialPosition = (isupper(colorAndType) && currentRow == 1) || (!isupper(colorAndType) && currentRow == 6);
    // If the pawn tries to move forward two squares
    if (isInitialPosition && newCol == currentCol && newRow == currentRow + (2 * direction)) {
        // Check if path is clear (no pieces in the way)
        std::string midPos = "";
        midPos += currentPos[0];
        midPos += (char)(currentRow + direction + '1');  // Middle position

        // Check if both the middle and destination squares are empty
        if (board->getPiece(midPos)->getColorAndType() != '#' || board->getPiece(newPos)->getColorAndType() != '#') {
            return INVALID_MOVE_ILLEGAL_MOVE;
        }
        return SUCCESSFUL_MOVE;
    }

    // Diagonal capture (one row forward and one column to the left or right)
    if (abs(newCol - currentCol) == 1 && newRow == currentRow + direction) {
        // Make sure there is a piece to capture
        ChessPiece* destPiece = board->getPiece(newPos);
        if (destPiece->getColorAndType() == '#') {  // No piece to capture
            return INVALID_MOVE_ILLEGAL_MOVE;
        }
        // Make sure the piece is of the opposite color
        bool isSameColor = (isupper(destPiece->getColorAndType()) == isupper(this->colorAndType));
        if (isSameColor) {
            return INVALID_MOVE_PIECE_OF_PLAYER;
        }
        // Check if the pawn is at the end of the board (promotion)
        if ((isupper(colorAndType) && newRow == 7) || (!isupper(colorAndType) && newRow == 0)) {
            return VALID_MOVE_PROMOTION;
        }
        return VALID_MOVE_ATE_PIECE;
    }

    // Check if the move puts the player in check (invalid)
    // Save a temporary board and apply the move to it - then check if the player is in check
    Board tempBoard(*board);
    tempBoard.movePiece(currentRow, currentCol, newRow, newCol);
    char color = isupper(this->colorAndType) ? 'w' : 'b';  // Get the color of the piece (to know on which side to check for check)

    // If checking for a check situation, ensure we avoid an infinite loop
    if (!isValidationCheck) {
        if (game->isInCheck(color, &tempBoard, true)) {
            return INVALID_MOVE_CAUSE_CHECK;
        }
    }

    return INVALID_MOVE_ILLEGAL_MOVE;
}


ChessPiece* Pawn::promote(std::string& pos, char type) const
{
	type = toupper(type);

    if (type == 'Q')
    {
		char color = (isupper(colorAndType) ? 'Q' : 'q');
		return new Queen(pos, color);
	}
    else if (type == 'R')
    {
		char color = (isupper(colorAndType) ? 'R' : 'r');
		return new Rook(pos, color);
	}
    else if (type == 'N')
    {
		char color = (isupper(colorAndType) ? 'N' : 'n');
		return new Knight(pos, color);
	}
    else if (type == 'B')
    {
		char color = (isupper(colorAndType) ? 'B' : 'b');
		return new Bishop(pos, color);
	}
    else
    {
		return nullptr;
    }
}