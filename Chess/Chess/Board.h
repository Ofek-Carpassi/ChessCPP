#pragma once
#ifndef BOARD_H
#define BOARD_H

#include "ChessPiece.h"

class Board
{
private:
	ChessPiece* board[8][8];

public:
	Board();

	~Board();

	// Getters
	ChessPiece* getPiece(std::string& pos) const;

	// Move a piece
	int movePiece(std::string& startPos, std::string& endPos, char currentPlayer);
};

#endif