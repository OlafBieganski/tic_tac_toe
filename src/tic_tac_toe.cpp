# include "../inc/tic_tac_toe.hh"

using namespace std;

TicTacToe::TicTacToe(uint _boardSize, uint _numToWin, bool whoStarts, bool playWithComp){
    // dynamically create board of sufficient size
    board = new char*[_boardSize];
    for(uint i = 0; i < _boardSize; i++){
        board[i] = new char[_boardSize];
    }
    // fill the game board with spaces
    for(uint i = 0; i < _boardSize; i++){
        for(uint j = 0; j < _boardSize; j++){
            board[i][j] = ' ';
        }
    }
    boardSize = _boardSize;
    numToWin = _numToWin;
    turn = whoStarts;
    if(playWithComp == true) O = COMPUTER;
}

TicTacToe::~TicTacToe(){
    for(uint i = 0; i < boardSize; i++){
        delete [] board[i];
    }
    delete [] board;
}

void TicTacToe::printBoard(){
    for(uint i = 0; i < boardSize; i++){
        for(uint j = 0; j < boardSize; j++){
            cout << "----";
        }
        cout << "-";
        cout << endl;
        for(uint j = 0; j < boardSize; j++){
            cout << "| " << board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    for(uint j = 0; j < boardSize; j++){
        cout << "----";
    }
    cout << "-";
    cout << endl;
}

bool TicTacToe::makeMove(uint cords){
    // check if cords are correct
    if(cords > boardSize*boardSize-1) return false;
    // check if place not filled
    uint row = cords / boardSize, column = cords % boardSize;
    if(board[row][column] != ' ') return false;
    // check which player's turn
    char sign;
    if(turn == true){
        sign = 'X';
    } else {
        sign = 'O';
    }
    board[row][column] = sign;
    return true;
}

bool TicTacToe::Win(){
    // check horizontal win
    for(uint i = 0; i < boardSize; i++){
        for(uint j = 0; j < boardSize - numToWin+1; j++){
            bool isWin = true;
            for(uint k = 0; k < numToWin; k++){
                if(board[i][j+k] != 'X'){
                    isWin = false;
                    break;
                }
            }
            if(isWin){
                state = WIN_X;
                //cout << "STATE: " <<  state << endl;
                return true;
            }
            isWin = true;
            for(uint k = 0; k < numToWin; k++){
                if(board[i][j+k] != 'O'){
                    isWin = false;
                    break;
                }
            }
            if(isWin){
                state = WIN_O;
                return true;
            }
        }
    }
    
    // check vertical win
    for(uint i = 0; i < boardSize; i++){
        for(uint j = 0; j < boardSize - numToWin+1; j++){
            bool isWin = true;
            for(uint k = 0; k < numToWin; k++){
                if(board[j+k][i] != 'X'){
                    isWin = false;
                    break;
                }
            }
            if(isWin){
                state = WIN_X;
                //cout << "STATE: " <<  state << endl;
                return true;
            }
            isWin = true;
            for(uint k = 0; k < numToWin; k++){
                if(board[j+k][i] != 'O'){
                    isWin = false;
                    break;
                }
            }
            if(isWin){
                state = WIN_O;
                return true;
            }
        }
    }

    // check diagonal win
    for(uint i = 0; i < boardSize - numToWin+1; i++){
        for(uint j = 0; j < boardSize - numToWin+1; j++){
            bool isWin = true;
            for(uint k = 0; k < numToWin; k++){
                if(board[i+k][j+k] != 'X'){
                    isWin = false;
                    break;
                }
            }
            if(isWin){
                state = WIN_X;
                //cout << "STATE: " <<  state << endl;
                return true;
            }
            isWin = true;
            for(uint k = 0; k < numToWin; k++){
                if(board[i+k][j+k] != 'O'){
                    isWin = false;
                    break;
                }
            }
            if(isWin){
                state = WIN_O;
                return true;
            }
        }
    }

    return false;
}

