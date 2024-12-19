#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include "Board.h"

class ChessPiece
{
private:
    std::string currentPos;
    char colorAndType;

public:
    ChessPiece(std::string pos, char colorAndType);

    ~ChessPiece();

    virtual std::string getCurrentPos() const;
    virtual  char getColorAndType() const;

    virtual void setPos(std::string& pos);

	virtual int isValidMove(std::string& currentPos, std::string& newPos, Board* board) const;
};

#endif