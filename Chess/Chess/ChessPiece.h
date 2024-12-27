#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include "Board.h"
#include "Game.h"

class Game;
class Board;

class ChessPiece
{
protected:
    std::string currentPos;
    char colorAndType;

public:
    virtual std::string getCurrentPos() const;
    virtual char getColorAndType() const;

    virtual void setPos(std::string& pos);

	// A pure virtual function that will be implemented by the derived classes
	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board, Game* game, bool isValidationCheck = false) const = 0;
};

#endif