#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class TicTacToe {
private:
    char board[3][3];
    char currentPlayer;
    int player1Wins;
    int player2Wins;
    int draws;

    void clearBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Reset board to numbers 1-9 for easy position selection
    void resetBoard() {
        char cell = '1';
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = cell++;
            }
        }
        currentPlayer = 'X';
    }

    // Print the dynamic game board to the console
    void displayBoard() const {
        cout << "\n";
        cout << "     |     |     \n";
        cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  \n";
        cout << "_____|_____|_____\n";
        cout << "     |     |     \n";
        cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  \n";
        cout << "_____|_____|_____\n";
        cout << "     |     |     \n";
        cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  \n";
        cout << "     |     |     \n";
        cout << "\n";
    }

    // Update board based on chosen position (1-9)
    bool placeMarker(int slot) {
        int row = (slot - 1) / 3;
        int col = (slot - 1) % 3;

        if (slot >= 1 && slot <= 9 && board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentPlayer;
            return true;
        }
        return false;
    }

    // Check row, column, and diagonal matching conditions
    bool checkWin() const {
        // Check Rows and Columns
        for (int i = 0; i < 3; i++) {
            if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
                (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
                return true;
            }
        }
        // Check Diagonals
        if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
            (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
            return true;
        }
        return false;
    }

    // Check if grid is completely filled without a winner
    bool checkDraw() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    return false;
                }
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

public:
    TicTacToe() : player1Wins(0), player2Wins(0), draws(0) {
        resetBoard();
    }

    void playSingleGame() {
        resetBoard();
        bool gameOver = false;

        while (!gameOver) {
            displayBoard();
            int slot;

            cout << "Player " << (currentPlayer == 'X' ? "1 (X)" : "2 (O)") 
                 << ", enter position (1-9): ";

            if (!(cin >> slot)) {
                cout << "\nInvalid input! Please enter a number between 1 and 9.\n";
                clearBuffer();
                continue;
            }

            if (!placeMarker(slot)) {
                cout << "\nInvalid move! Slot is either occupied or out of bounds.\n";
                continue;
            }

            if (checkWin()) {
                displayBoard();
                cout << "=========================================\n";
                cout << "  Player " << (currentPlayer == 'X' ? "1 (X)" : "2 (O)") << " Wins the Game!\n";
                cout << "=========================================\n";
                
                if (currentPlayer == 'X') player1Wins++;
                else player2Wins++;
                
                gameOver = true;
            } else if (checkDraw()) {
                displayBoard();
                cout << "=========================================\n";
                cout << "         Game Ended in a Draw!          \n";
                cout << "=========================================\n";
                draws++;
                gameOver = true;
            } else {
                switchPlayer();
            }
        }
    }

    void showScoreboard() const {
        cout << "\n=========================================\n";
        cout << "               SCOREBOARD                \n";
        cout << "=========================================\n";
        cout << "  Player 1 (X) Wins : " << player1Wins << "\n";
        cout << "  Player 2 (O) Wins : " << player2Wins << "\n";
        cout << "  Total Draws       : " << draws << "\n";
        cout << "=========================================\n";
    }

    void start() {
        char playAgain;
        cout << "=========================================\n";
        cout << "      WELCOME TO TIC-TAC-TOE (C++)       \n";
        cout << "=========================================\n";

        do {
            playSingleGame();
            showScoreboard();

            cout << "\nDo you want to play another round? (y/n): ";
            cin >> playAgain;
            clearBuffer();

        } while (playAgain == 'y' || playAgain == 'Y');

        cout << "\nThanks for playing! Final scores recorded.\n";
    }
};

int main() {
    TicTacToe game;
    game.start();
    return 0;
}