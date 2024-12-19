#include "Player.h"

Player::Player(char color, King* king) : color(color), isInCheck(false), king(king) {}
{}

Player::~Player()
{}

King* Player::getKing() const
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

void Player::setKing(King* king)
{
	this->king = king;
}