#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>

class ChessPiece
{
private:
	std::string currentPos;
	char colorAndType;

public:
	ChessPiece(std::string& pos, char colorAndType);

	~ChessPiece();

	std::string getCurrentPos() const;
	char getColorAndType() const;

	void setPos(std::string& pos);

	virtual bool isValidMove(std::string& newPos) const;
};

#endif