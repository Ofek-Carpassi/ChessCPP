#include "Game.h"
#include "Pawn.h"
#include "NullPiece.h"

void Game::switchPlayer() {
    // Switch the current player
    currentPlayer = (currentPlayer == 'w') ? 'b' : 'w';
}

std::string Game::checkMove(std::string move)
{
	std::string returnVal = "-1";

    // Get the start and end positions
    std::string startPos = move.substr(0, 2);
    std::string endPos = move.substr(2, 2);

    // Get the piece at start position
    ChessPiece* piece = board->getPiece(startPos);

    // Check if there is a piece at the starting position
    if (piece->getColorAndType() == '#') {
        std::cout << "No piece at starting position!\n";
		return "2\0";
    }

    // Check if the piece belongs to the current player
    bool isPieceWhite = isupper(piece->getColorAndType());
    if ((currentPlayer == 'w' && !isPieceWhite) || (currentPlayer == 'b' && isPieceWhite)) {
        std::cout << "That's not your piece!\n";
		return "2\0";
    }

    // Check if the move is valid and handle the result accordingly
    int moveResult = piece->isValidMove(startPos, endPos, board, this);

    switch (moveResult) {
    case SUCCESSFUL_MOVE:
    case VALID_MOVE_ATE_PIECE:
    case VALID_MOVE_PROMOTION:
    {
        // The move was successful, so move the piece

        // Translate the move to row and column indices
        int startRow = startPos[1] - '1';
        int startCol = startPos[0] - 'a';
        int endRow = endPos[1] - '1';
        int endCol = endPos[0] - 'a';

        if (moveResult == VALID_MOVE_PROMOTION) {
            // Get the promotion type from the user
            char promotionType = '0';
            do {
                std::cout << "Promote to (Q, R, N, B): ";
                std::cin >> promotionType;
                promotionType = toupper(promotionType);
            } while (promotionType != 'Q' && promotionType != 'R' && promotionType != 'N' && promotionType != 'B');

            // Promote the pawn
            ChessPiece* promotedPiece = dynamic_cast<Pawn*>(piece)->promote(endPos, promotionType);
            board->setPiece(endRow, endCol, promotedPiece);

            // Remove the pawn from the board
            board->setPiece(startRow, startCol, new NullPiece(startPos));
        }
        else {
            // Move the piece to the new position
            board->movePiece(startRow, startCol, endRow, endCol);
        }

        // Get the new board
        boardString = board->toString();

        // change player
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

    // Update the return val to a string of <moveResultCode><NULL>
    returnVal = std::to_string(moveResult) + "\0";

	return returnVal;
}

Game::Game() {
    // Make it so that the white player starts first and create the board
    currentPlayer = 'w';
    board = new Board();

    // Get the king pieces for each player
    std::string kingPos = "e1";
    ChessPiece* king = board->getPiece(kingPos);
    whitePlayer = new Player('w', king);

    kingPos = "e8";
    king = board->getPiece(kingPos);
    blackPlayer = new Player('b', king);

    // Set the game to be in play
    isInPlay = false;

	boardString = "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1";
}

Game::~Game() {
    // Delete all the elements that are dynamically allocated
    delete board;
    delete whitePlayer;
    delete blackPlayer;
}

bool Game::isInCheck(char color, Board* gameBoard, bool isValidationCheck) {
    // Check if we got a board from the function call or use the default board (we will get one fron isValidMove)
    Board* boardToUse = gameBoard ? gameBoard : this->board;

    // Get the current player's king position
    Player* player = (color == 'w') ? whitePlayer : blackPlayer;
    ChessPiece* king = player->getKing();
    std::string kingPos = king->getCurrentPos();

    // Iterate over the entire board and for each piece check if it can attack the king
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            // Translate the row and column to a position
            std::string pos = "";
            pos += (char)(col + 'a');
            pos += (char)(row + '1');

            // Get the piece at the position
            ChessPiece* piece = boardToUse->getPiece(pos);
            if (piece->getColorAndType() == '0') continue; // Skip if there is no piece

            // Get the color of the piece
            char pieceColor = (piece->getColorAndType() >= 'a') ? 'b' : 'w';

            // If the piece is not the same color as the king (it can attack the king)
            if (pieceColor != color) {
                // Check if the piece can attack the king
                if (!isValidationCheck)
                {
                    // Check if the move is valid and make sure we don't check for check (not get into this if again)
                    int moveResult = piece->isValidMove(pos, kingPos, boardToUse, this, true);

                    // If the piece can eat the king, the player is in check
                    if (moveResult == VALID_MOVE_ATE_PIECE) {
                        player->setIsInCheck(true);
                        return true;
                    }
                }
                // If there is no need for validation (called from isValidMove), check if the piece can attack the king
                else
                {
                    // Get the positions in terms of row and column in the array
                    int currentRow = pos[1] - '1';
                    int currentCol = pos[0] - 'a';
                    int kingRow = kingPos[1] - '1';
                    int kingCol = kingPos[0] - 'a';

                    // Simple path checking without recursion
                    bool canMove = true;
                    // basic movement validation for each piece type based on its rules
                    switch (toupper(piece->getColorAndType())) {
                    case 'P':
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