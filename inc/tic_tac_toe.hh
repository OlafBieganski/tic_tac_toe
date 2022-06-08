#include "iostream"

enum player {PLAYER1, PLAYER2, COMPUTER};
enum gameStatus {WIN_X, TIE, WIN_O};
//enum moves {A, B, C, D, E, F, G, H, I};

class TicTacToe {
    char* board = new char[9];
    player X = PLAYER1, O = PLAYER2;
    bool turn = true; // true = X, flase = O
    uint numToWin = 3;
    public:
    TicTacToe();
    TicTacToe(uint boardSize, uint _numToWin, bool whoStarts, bool playWithComp);
    ~TicTacToe();
    int evaluateBoard();
    bool makeMove(uint cords);
    gameStatus Win();
    void printBoard();
    uint findBestMv();
    int minimax();
};