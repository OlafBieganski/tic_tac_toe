#ifndef TICTACTOE
#define TICTACTOE
#include "iostream"

enum player {PLAYER1, PLAYER2, COMPUTER};
enum gameStatus {WIN_X, TIE, WIN_O, NO_END};

class TicTacToe {
    char** board;
    uint boardSize;
    player X = PLAYER1, O = PLAYER2;
    bool turn = true; // true = X, flase = O
    uint numToWin = 3;
    gameStatus state = NO_END;

    public:
    TicTacToe();
    TicTacToe(uint _boardSize, uint _numToWin, bool whoStarts, bool playWithComp);
    ~TicTacToe();
    int evaluateBoard();
    bool makeMove(uint cords);
    bool Win();
    void printBoard();
    uint findBestMv();
    int minimax();
    void getUserInput();
};

#endif