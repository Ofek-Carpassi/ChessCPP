#pragma once
#ifndef BOARD_H
#define BOARD_H

#define COL 8
#define ROW 8

#include "ChessPiece.h"

class ChessPiece;

class Board
{
private:
	ChessPiece* board[COL][ROW];

public:
	Board();

	~Board();

	// Getters
	ChessPiece* getPiece(std::string& pos) const;

	// Move a piece
	int movePiece(std::string& startPos, std::string& endPos, char currentPlayer);
};

#endif