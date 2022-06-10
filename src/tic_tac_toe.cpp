# include "../inc/tic_tac_toe.hh"

using namespace std;

TicTacToe::TicTacToe(uint _boardSize, uint _numToWin, bool whoStarts, bool playWithComp){
    // dynamically create board of sufficient size
    board = new char*[_boardSize];
    for(int i = 0; i < _boardSize; i++){
        board[i] = new char[_boardSize];
    }
    // fill the game board with spaces
    for(int i = 0; i < _boardSize; i++){
        for(int j = 0; j < _boardSize; j++){
            board[i][j] = ' ';
        }
    }
    boardSize = _boardSize;
    numToWin = _numToWin;
    turn = whoStarts;
    if(playWithComp == true) O = COMPUTER;
}

TicTacToe::~TicTacToe(){
    for(int i = 0; i < boardSize; i++){
        delete [] board[i];
    }
    delete [] board;
}

void TicTacToe::printBoard(){
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            cout << "----";
        }
        cout << endl;
        for(int j = 0; j < boardSize; j++){
            cout << "| " << board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    for(int j = 0; j < boardSize; j++){
        cout << "----";
    }
}