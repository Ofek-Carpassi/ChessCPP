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
    
    // Methods for the game handling
    void displayBoard() const;
    void switchPlayer();
    bool isValidMoveFormat(const std::string& move) const;
    std::string handleMove();
    void printCurrentPlayerTurn() const;

public:
	// Constructors and Destructors
    Game();
    ~Game();
    void startGame();
    bool isInCheck(char color, Board* gameBoard, bool isValidationCheck = false);
};

#endif