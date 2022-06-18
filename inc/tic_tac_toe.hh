#ifndef TICTACTOE
#define TICTACTOE
#include <iostream>

enum player {PLAYER1, PLAYER2, COMPUTER};
enum gameStatus {WIN_X, TIE, WIN_O, NO_END};

class TicTacToe {
    char** board = nullptr;
    uint boardSize = 0;
    player X = PLAYER1, O = PLAYER2;
    // true = X, flase = O
    bool turn = true;
    uint numToWin = 3;
    gameStatus state = NO_END;

    public:
    TicTacToe();
    TicTacToe(uint _boardSize, uint _numToWin, bool whoStarts, bool playWithComp);
    ~TicTacToe();
    TicTacToe(const TicTacToe & obj);
    int evaluateBoard();
    bool makeMove(uint cords);
    bool Win();
    bool isMvPsbl(uint cords);
    uint movesLeft();
    void printBoard();
    uint findBestMv(bool isMaxi);
    void askForMove();
    void startGame();
    friend int minimax(TicTacToe game, uint depth, int alpha, int beta, bool isMaxi);
    TicTacToe & operator=(const TicTacToe & obj);
};

TicTacToe initialize_Game();
// calculates best move given curretn state of the board
int minimax(TicTacToe game, uint depth, int alpha, int beta,  bool isMaxi);

#endif