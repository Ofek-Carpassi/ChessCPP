#include "Player.h"

Player::Player(char color, ChessPiece* king) : color(color), isInCheck(false), king(king)
{}

Player::~Player()
{}

ChessPiece* Player::getKing() const
{
	return king;
}

bool Player::getIsInCheck() const
{
	return isInCheck;
}

void Player::setIsInCheck(bool isInCheck)
{
	this->isInCheck = isInCheck;
}

void Player::setKing(ChessPiece* king)
{
	this->king = king;
}