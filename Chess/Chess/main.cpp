#include "Bishop.h"
#include "ChessPiece.h"
#include "Board.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Player.h"

#include <iostream>
#include <cassert>

void testBishop() {
	Board board = Board();
	std::string pos = "c1";
	std::string newPos = "e3";

	std::cout << "Testing Bishop" << std::endl;
	ChessPiece* bishop = board.getPiece(pos);
	assert(bishop->isValidMove(pos, newPos, &board) == 6);
	std::cout << "Expected: 6" << std::endl;
	std::cout << "Actual: " << bishop->isValidMove(pos, newPos, &board) << std::endl;

}

int main() {
    testBishop();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}