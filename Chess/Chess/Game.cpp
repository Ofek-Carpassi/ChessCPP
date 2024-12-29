#include "Game.h"
#include "Pawn.h"
#include "NullPiece.h"

void Game::displayBoard(){
    int indx = 0;
	// Print the board piece by piece (also print the row and column labels)
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
            msgToGraphics[indx] = piece;
            indx++;
        }
        
        std::cout << "|" << row + 1 << "\n";
    }
    std::cout << "  ---------------\n";
    std::cout << "  a b c d e f g h\n\n";
}

void Game::switchPlayer() {
	// Switch the current player
    currentPlayer = (currentPlayer == 'w') ? 'b' : 'w';
}

bool Game::isValidMoveFormat(const std::string& move) const {
	// Check if the length is 4 and if the positions are within the board
    return move.length() == 4 &&
        move[0] >= 'a' && move[0] <= 'h' &&
        move[1] >= '1' && move[1] <= '8' &&
        move[2] >= 'a' && move[2] <= 'h' &&
        move[3] >= '1' && move[3] <= '8';
}

void Game::printCurrentPlayerTurn(){
	// Print the current player's turn
    if (currentPlayer == 'w')
    {
        std::cout << "\n" << "White";
        msgToGraphics[64] = '0';
    }
    else
    {
        std::cout << "\n" << "Black";
        msgToGraphics[64] = '1';
    }

    std::cout << "'s turn\n";
}

std::string Game::handleMove() {
	// Get the move from the user
    std::string move;
    do {
		// Print the prompt and get the move
        //std::cout << "Enter move (e.g., e2e4): ";
        //std::cin >> move;

        // get message from graphics
        move = p.getMessageFromGraphics();
        
		// Check if the user wants to quit - if so, end the game
        if (move == "quit" || move == "exit") {
            isInPlay = false;
            return "";
        }

		// Check if the move is in the correct format
        if (!isValidMoveFormat(move)) {
            std::cout << "Invalid format. Use format like 'e2e4'\n";
            continue;
        }
    } while (!isValidMoveFormat(move));

	// return the move if it's valid
    return move;
}

void Game::startGame() {
	// Welcome message
    //std::cout << "\nWelcome to Console Chess!\n";
    //std::cout << "Enter moves in format: from-to (e.g., e2e4)\n";
    //std::cout << "Enter 'quit' or 'exit' to end game\n";

    srand(time_t(NULL));
    
    bool isConnect = p.connect();

    std::string ans;
    while (!isConnect)
    {
        std::cout << "cant connect to graphics" << std::endl;
        std::cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << std::endl;
        std::cin >> ans;

        if (ans == "0")
        {
            std::cout << "trying connect again.." << std::endl;
            Sleep(5000);
            isConnect = p.connect();
        }
        else
        {
            p.close();
            return;
        }
    }

    
	// While not checkmate or quit
    isInPlay = true;
    while (isInPlay) {
        // Print the current state
        
        displayBoard();
        printCurrentPlayerTurn();
        msgToGraphics[65] = '\0';

        p.sendMessageToGraphics(msgToGraphics);   // send the board string

		// Handle the move and make sure we are still playing
        std::string move = handleMove();
        if (!isInPlay) break;

		// Get the start and end positions
        std::string startPos = move.substr(0, 2);
        std::string endPos = move.substr(2, 2);

        // Get the piece at start position
        ChessPiece* piece = board->getPiece(startPos);

		// Check if there is a piece at the starting position
        if (piece->getColorAndType() == '#') {
            std::cout << "No piece at starting position!\n";

            char* msg = NULL;
            msg += INVALID_MOVE_NO_PIECE + '0';
            msg += 0;
            p.sendMessageToGraphics(msg);
            continue;
        }

		// Check if the piece belongs to the current player
        bool isPieceWhite = isupper(piece->getColorAndType());
        if ((currentPlayer == 'w' && !isPieceWhite) || (currentPlayer == 'b' && isPieceWhite)) {
            std::cout << "That's not your piece!\n";

            char* msg = NULL;
            msg += INVALID_MOVE_NO_PIECE + '0';
            msg += 0;
            p.sendMessageToGraphics(msg);
            continue;
        }
        std::cout << "\n----------\n" << startPos << "\n" << endPos << "\n----------\n";
		// Check if the move is valid and handle the result accordingly
        int moveResult = piece->isValidMove(startPos, endPos, board, this);
        std::cout << "\n----------\n" << moveResult << "\n----------\n";
        char msg[2];

        switch (moveResult) {
        case SUCCESSFUL_MOVE:
        { 
            msg[0] = (char)(0 + '0');
            break;
        }
        case VALID_MOVE_ATE_PIECE:
        {
            msg[0] = (char)(1 + '0');
            break;
        }
        case VALID_MOVE_PROMOTION:
        {
			// The move was successful, so move the piece
            msg[0] = (char)(9 + '0');
            
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
            
			// change player
            switchPlayer();
        }
        break;

        case INVALID_MOVE_NO_PIECE:
            std::cout << "No piece at starting position!\n";
            msg[0] = (char)(2 + '0');
            break;
        case INVALID_MOVE_PIECE_OF_PLAYER:
            std::cout << "Cannot capture your own piece!\n";
            msg[0] = (char)(3 + '0');
            break;
        case INVALID_MOVE_CAUSE_CHECK:
            std::cout << "Move would put/leave you in check!\n";
            msg[0] = (char)(4 + '0');
            break;
        case INVALID_MOVE_OUT_OF_BOUNDS:
            std::cout << "Move is out of bounds!\n";
            msg[0] = (char)(5 + '0');
            break;
        case INVALID_MOVE_ILLEGAL_MOVE:
            std::cout << "Illegal move for this piece!\n";
            msg[0] = (char)(6 + '0');
            break;
        case INVALID_MOVE_SAME_POS:
            std::cout << "Start and end positions are the same!\n";
            msg[0] = (char)(7 + '0');
            break;
        default:
            std::cout << "Invalid move!\n";
            break;
        }
        msg[1] = 0;
        p.sendMessageToGraphics(msg);
    }

    std::cout << "\nGame Over!\n";
    p.close();
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