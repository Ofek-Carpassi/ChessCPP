#pragma once
#ifndef BOARD_H
#define BOARD_H

#define COL 8
#define ROW 8

#include "ChessPiece.h"
#include "Game.h"

class Game;
class ChessPiece;

class Board
{
private:
	// 2D array of ChessPiece pointers
	ChessPiece* board[COL][ROW];

public:
	Board();

	// Copy constructor
	Board(const Board& other);

	~Board();

	// Getters
	ChessPiece* getPiece(std::string& pos) const;

	// Move a piece
	void movePiece(int currentRow, int currentCol, int newRow, int newCol);

	void setPiece(int row, int col, ChessPiece* piece);

	std::string toString() const;
};

#endif