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

void testPawn() {
	Board board = Board();
	std::string currentPos = "a7";
	std::string newPos = "a6";

	ChessPiece* pawn = board.getPiece(currentPos);

	std::cout << pawn->isValidMove(currentPos, newPos, &board) << std::endl;

	newPos = "a5";
	std::cout << pawn->isValidMove(currentPos, newPos, &board) << std::endl;

	newPos = "b6";
	std::cout << pawn->isValidMove(currentPos, newPos, &board) << std::endl;
}

int main() {

	std::string currentPos = "e1";
	std::string newPos = "a2";

	Board board = Board();

	ChessPiece* piece = board.getPiece(currentPos);

	std::cout << piece->isValidMove(currentPos, newPos, &board) << std::endl;

	testPawn();


    std::cout << "All tests passed!" << std::endl;
    return 0;
}