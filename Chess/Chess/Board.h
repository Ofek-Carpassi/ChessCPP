#pragma once
#ifndef BOARD_H
#define BOARD_H

#include "ChessPiece.h"
#include <vector>

class Board
{
private:
	std::vector<std::vector<ChessPiece*>> board;

public:
	Board();

	~Board();

	// Getters
	ChessPiece* getPieceAt(std::string& pos) const;

	// Get the board
	std::vector<std::vector<ChessPiece*>> getBoard() const;

	// Move a piece
	int movePiece(std::string& startPos, std::string& endPos);
};

#endif