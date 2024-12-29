#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>
#include "Board.h"
#include "Player.h"
#include <iostream>
#include "MoveCase.h"

class Board;
class Player;

class Game {
private:
    // Variables
    char currentPlayer;
    Player* whitePlayer;
    Player* blackPlayer;
    Board* board;
    bool isInPlay;

    std::string boardString;

    void switchPlayer();

public:
    // Constructors and Destructors
    Game();
    ~Game();
    std::string checkMove(std::string move);
    bool isInCheck(char color, Board* gameBoard, bool isValidationCheck = false);
};

#endif