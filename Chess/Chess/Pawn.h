#pragma once
#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"

class Pawn : public ChessPiece
{
public:
	Pawn(std::string& pos, char colorAndType);

	~Pawn();

	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck) const override;

	ChessPiece* promote(std::string& pos, char type) const;
};

#endif