#include "Game.h"

// Game.cpp
void Game::displayBoard() const {
    std::cout << "\n  a b c d e f g h\n";
    std::cout << "  ---------------\n";

    for (int row = 7; row >= 0; row--) {
        std::cout << row + 1 << "|";
        for (int col = 0; col < 8; col++) {
            std::string pos = "";
            pos += (char)(col + 'a');
            pos += (char)(row + '1');
            char piece = board->getPiece(pos)->getColorAndType();
            std::cout << piece << " ";
        }
        std::cout << "|" << row + 1 << "\n";
    }
    std::cout << "  ---------------\n";
    std::cout << "  a b c d e f g h\n\n";
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == 'w') ? 'b' : 'w';
}

bool Game::isValidMoveFormat(const std::string& move) const {
    return move.length() == 4 &&
        move[0] >= 'a' && move[0] <= 'h' &&
        move[1] >= '1' && move[1] <= '8' &&
        move[2] >= 'a' && move[2] <= 'h' &&
        move[3] >= '1' && move[3] <= '8';
}

void Game::printCurrentPlayerTurn() const {
    std::cout << "\n" << (currentPlayer == 'w' ? "White" : "Black") << "'s turn\n";
}

std::string Game::handleMove() {
    std::string move;
    do {
        std::cout << "Enter move (e.g., e2e4): ";
        std::cin >> move;

        if (move == "quit" || move == "exit") {
            isInPlay = false;
            return "";
        }

        if (!isValidMoveFormat(move)) {
            std::cout << "Invalid format. Use format like 'e2e4'\n";
            continue;
        }
    } while (!isValidMoveFormat(move));

    return move;
}

void Game::startGame() {
    std::cout << "\nWelcome to Console Chess!\n";
    std::cout << "Enter moves in format: from-to (e.g., e2e4)\n";
    std::cout << "Enter 'quit' or 'exit' to end game\n";

    isInPlay = true;

    while (isInPlay) {
        displayBoard();
        printCurrentPlayerTurn();

        std::string move = handleMove();
        if (!isInPlay) break;

        std::string startPos = move.substr(0, 2);
        std::string endPos = move.substr(2, 2);

        // Get the piece at start position
        ChessPiece* piece = board->getPiece(startPos);

        // Check if piece exists and belongs to current player
        if (piece->getColorAndType() == '0') {
            std::cout << "No piece at starting position!\n";
            continue;
        }

        bool isPieceWhite = isupper(piece->getColorAndType());
        if ((currentPlayer == 'w' && !isPieceWhite) ||
            (currentPlayer == 'b' && isPieceWhite)) {
            std::cout << "That's not your piece!\n";
            continue;
        }

        // Try to make the move
        int moveResult = piece->isValidMove(startPos, endPos, board, this);

        switch (moveResult) {
        case SUCCESSFUL_MOVE:
        case VALID_MOVE_ATE_PIECE:
        {
            int startRow = startPos[1] - '1';
            int startCol = startPos[0] - 'a';
            int endRow = endPos[1] - '1';
            int endCol = endPos[0] - 'a';
            board->movePiece(startRow, startCol, endRow, endCol);

            // Check if opponent is in check
            char opponentColor = (currentPlayer == 'w') ? 'b' : 'w';
            if (isInCheck(opponentColor, board, false)) {
                std::cout << "Check!\n";
            }

            switchPlayer();
        }
        break;

        case INVALID_MOVE_NO_PIECE:
            std::cout << "No piece at starting position!\n";
            break;
        case INVALID_MOVE_PIECE_OF_PLAYER:
            std::cout << "Cannot capture your own piece!\n";
            break;
        case INVALID_MOVE_CAUSE_CHECK:
            std::cout << "Move would put/leave you in check!\n";
            break;
        case INVALID_MOVE_OUT_OF_BOUNDS:
            std::cout << "Move is out of bounds!\n";
            break;
        case INVALID_MOVE_ILLEGAL_MOVE:
            std::cout << "Illegal move for this piece!\n";
            break;
        case INVALID_MOVE_SAME_POS:
            std::cout << "Start and end positions are the same!\n";
            break;
        default:
            std::cout << "Invalid move!\n";
        }
    }

    std::cout << "\nGame Over!\n";
}

Game::Game() {
    currentPlayer = 'w';
    board = new Board();

    std::string kingPos = "e1";
    ChessPiece* king = board->getPiece(kingPos);
    whitePlayer = new Player('w', king);

    kingPos = "e8";
    king = board->getPiece(kingPos);
    blackPlayer = new Player('b', king);

    isInPlay = false;
}

Game::~Game() {
    delete board;
    delete whitePlayer;
    delete blackPlayer;
}

bool Game::isInCheck(char color, Board* gameBoard, bool isValidationCheck) {
    Board* boardToUse = gameBoard ? gameBoard : this->board;

    Player* player = (color == 'w') ? whitePlayer : blackPlayer;
    ChessPiece* king = player->getKing();
    std::string kingPos = king->getCurrentPos();

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            std::string pos = "";
            pos += (char)(col + 'a');
            pos += (char)(row + '1');

            ChessPiece* piece = boardToUse->getPiece(pos);
            if (piece->getColorAndType() == '0') continue;

            char pieceColor = (piece->getColorAndType() >= 'a') ? 'b' : 'w';
            if (pieceColor != color) {
                // When validating moves, skip the check validation to prevent recursion
                if (!isValidationCheck) {
                    // Basic move validation without check validation
					int moveResult = piece->isValidMove(pos, kingPos, boardToUse, this, true);
                    if (moveResult == SUCCESSFUL_MOVE || moveResult == VALID_MOVE_ATE_PIECE) {
                        player->setIsInCheck(true);
                        return true;
                    }
                }
                else {
                    // For validation checks, only verify basic movement rules
                    int currentRow = pos[1] - '1';
                    int currentCol = pos[0] - 'a';
                    int kingRow = kingPos[1] - '1';
                    int kingCol = kingPos[0] - 'a';

                    // Simple path checking without recursion
                    bool canMove = true;
                    // Add basic movement validation for each piece type based on its rules
                    switch (toupper(piece->getColorAndType())) {
                    case 'P':
                        // Pawn capture rules
                        if (abs(kingCol - currentCol) == 1 &&
                            ((pieceColor == 'w' && kingRow == currentRow + 1) ||
                                (pieceColor == 'b' && kingRow == currentRow - 1))) {
                            return true;
                        }
                        break;
                    case 'R':
                        if (kingRow == currentRow || kingCol == currentCol) {
                            return true;
                        }
                        break;
                    case 'B':
                        if (abs(kingRow - currentRow) == abs(kingCol - currentCol)) {
                            return true;
                        }
                        break;
                    case 'N':
                        if ((abs(kingRow - currentRow) == 2 && abs(kingCol - currentCol) == 1) ||
                            (abs(kingRow - currentRow) == 1 && abs(kingCol - currentCol) == 2)) {
                            return true;
                        }
                        break;
                    case 'Q':
                        if (kingRow == currentRow || kingCol == currentCol ||
                            abs(kingRow - currentRow) == abs(kingCol - currentCol)) {
                            return true;
                        }
                        break;
                    }
                }
            }
        }
    }

    player->setIsInCheck(false);
    return false;
}