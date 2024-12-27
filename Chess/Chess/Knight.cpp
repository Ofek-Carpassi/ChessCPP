#include "Knight.h"

Knight::Knight(std::string pos, char colorAndType)
{
	this->currentPos = pos;
	this->colorAndType = colorAndType;
}

Knight::~Knight()
{
}

int Knight::isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const 
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

    // Knight moves in L-shape: 2 squares in one direction and 1 in perpendicular
    bool isValidKnightMove = (abs(newRow - currentRow) == 2 && abs(newCol - currentCol) == 1) ||
        (abs(newRow - currentRow) == 1 && abs(newCol - currentCol) == 2);

    if (!isValidKnightMove) {
        return INVALID_MOVE_ILLEGAL_MOVE;
    }
    
	// Check if the destination has a piece of the same color (if they do, the move is invalid)
    ChessPiece* destPiece = board->getPiece(newPos);
    bool isSameColor = (destPiece->getColorAndType() != '0' &&
        (isupper(destPiece->getColorAndType()) == isupper(this->colorAndType)));

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
    return (destPiece->getColorAndType() != '0') ? VALID_MOVE_ATE_PIECE : SUCCESSFUL_MOVE;
}