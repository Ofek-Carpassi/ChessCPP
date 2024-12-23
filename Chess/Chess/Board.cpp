#include "Board.h"
#include "ChessPiece.h"
#include "NullPiece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

Board::Board()
{
	// Initialize the board with nullptrs
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			// Translates the indexes to the position on the board (<letter><number>)
			std::string pos = "";
			pos += (char)(j + 'a');
			pos += (char)(i + '1');
			board[i][j] = new NullPiece(pos);
		}
	}

	// Initialize the white pieces
	board[0][0] = new Rook("a1", 'R');
	board[0][1] = new Knight("b1", 'N');
	board[0][2] = new Bishop("c1", 'B');
	board[0][3] = new Queen('Q');
	board[0][4] = new King('K');
	board[0][5] = new Bishop("f1", 'B');
	board[0][6] = new Knight("g1", 'N');
	board[0][7] = new Rook("h1", 'R');
	for (int i = 0; i < 8; i++)
	{
		std::string pos = "";
		pos += (char)(i + 'a');
		pos += '2';
		board[1][i] = new Pawn(pos, 'P');
	}

	// Initialize the black pieces
	board[7][0] = new Rook("a8", 'r');
	board[7][1] = new Knight("b8", 'n');
	board[7][2] = new Bishop("c8", 'b');
	board[7][3] = new Queen('q');
	board[7][4] = new King('k');
	board[7][5] = new Bishop("f8", 'b');
	board[7][6] = new Knight("g8", 'n');
	board[7][7] = new Rook("h8", 'r');
	for (int i = 0; i < 8; i++)
	{
		std::string pos = "";
		pos += (char)(i + 'a');
		pos += '7';
		board[6][i] = new Pawn(pos, 'p');
	}
}

Board::~Board()
{
	// Delete all the pieces
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete board[i][j];
		}
	}
}

ChessPiece* Board::getPiece(std::string& pos) const
{
	// The pos will be in format "a1" to "h8"
	int row = pos[1] - '1';
	int col = pos[0] - 'a';
	return board[row][col];
}

int Board::movePiece(std::string& startPos, std::string& endPos, char currentPlayer)
{
	// Not implemented
	// Should return:
	// 0 if the move was successful
	// 1 - Valid move, ate a piece
	// 2 - invalid move - in the source pos there is no piece of the current player
	// 3 - invalid move - in the destination pos there is a piece of the current player
	// 4 - invalid move - the move will cause a check on the current player
	// 5 - invalid move - the indexes of the positions are out of bounds
	// 6 - invalid move - illegal move for the piece
	// 7 - invalid move - the source and destination positions are the same
	// 8 - valid move - checkmate - BONUS

	return -1;
}