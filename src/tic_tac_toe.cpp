# include "../inc/tic_tac_toe.hh"
#include <limits.h>

using namespace std;

#define LOG(x) cout << x <<endl;
#define INF 2000000000

uint MAX_DEPTH = 0;

TicTacToe initialize_Game(){
    uint boardSize;
    bool playComp, whoStart;
    char choice;
    uint numOfSym;

    LOG("Type the size of the board you want to play on:");
    cin >> boardSize;

    LOG("Choose the number of symbols in a row for a win:");
    cin >> numOfSym;

    do{
        LOG("Do you want to play with computer or another player? (y/n)");
        cin >> choice;
    }while(choice != 'y' && choice != 'n');
    playComp = (choice == 'y');

    do{
        LOG("Who starts? You or the other player/computer? (y/n)");
        cin >> choice;
    }while(choice != 'y' && choice != 'n');
    whoStart = (choice == 'y');

    TicTacToe new_game(boardSize, numOfSym, whoStart, playComp);
    cout << endl;

    return new_game;
}

void TicTacToe::startGame(){
    switch (this->O){        
    case PLAYER2:
        printBoard();
        while(!Win()){
            askForMove();
            printBoard();
        }
        switch(state){
            case WIN_X:
            LOG("PLAYER 1 wins the game.");
            break;
            case WIN_O:
            LOG("PLAYER 2 wins the game.");
            break;
            case TIE:
            LOG("Game ends with tie. Nobody wins.");
            break;
            default:
            LOG("Something went wrong.");
        }
        break;

    case COMPUTER:
        printBoard();
        while(!Win()){
            askForMove();
            printBoard();
        }
        switch(state){
            case WIN_X:
            LOG("PLAYER 1 wins the game.");
            break;
            case WIN_O:
            LOG("COMPUTER wins the game.");
            break;
            case TIE:
            LOG("Game ends with tie. Nobody wins.");
            break;
            default:
            LOG("Something went wrong.");
        }
        break;
    }
}

void TicTacToe::askForMove(){
    if(turn){
        LOG("PLAYER's 1 turn.");
    } else {
        switch(O){
            case PLAYER2:
            LOG("PLAYER's 2 turn.");
            break;

            case COMPUTER:
            LOG("COMPUTER's turn.");
            uint compMv = findBestMv(true);
            this->makeMove(compMv);
            return;
        }
    }
    LOG("Type the number of cell you want place your sign:");
    uint num = -1;
    cin >> num;
    while (num < 0 && num > boardSize*boardSize-1){
        LOG("Number of cell is out of the correct scope.");
        cin >> num;
    }
    bool good;
    do{
        good = this->makeMove(num);
        if(!good){
            LOG("Invalid move. Try again!");
            cin >> num;
        }
    }while(!good);
}

TicTacToe::TicTacToe(const TicTacToe & obj){
    boardSize = obj.boardSize;
    X = obj.X, O = obj.O;
    turn = obj.turn;
    numToWin = obj.numToWin;
    state = obj.state;
    // dynamically create board of sufficient size
    board = new char*[boardSize];
    for(uint i = 0; i < boardSize; i++){
        board[i] = new char[boardSize];
    }
    // copy values from obj
    for(uint i = 0; i < boardSize; i++){
        for(uint j = 0; j < boardSize; j++){
            board[i][j] = obj.board[i][j];
        }
    }
}

TicTacToe & TicTacToe::operator=(const TicTacToe & obj){
    // handling self assignment
    if(this == &obj) return *this;
    boardSize = obj.boardSize;
    X = obj.X, O = obj.O;
    turn = obj.turn;
    numToWin = obj.numToWin;
    state = obj.state;
    if(board != nullptr){
        for(uint i = 0; i < boardSize; i++){
            delete [] board[i];
        }
        delete [] board;
    }
    // dynamically create board of sufficient size
    board = new char*[boardSize];
    for(uint i = 0; i < boardSize; i++){
        board[i] = new char[boardSize];
    }
    // copy values from obj
    for(uint i = 0; i < boardSize; i++){
        for(uint j = 0; j < boardSize; j++){
            board[i][j] = obj.board[i][j];
        }
    }
    return *this;
}

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

bool TicTacToe::isMvPsbl(uint cords){
    // check if cords are correct
    if(cords > boardSize*boardSize-1){
        // just to check if minimax correct
        cerr << "Error in isMvPsbl. Cordinates out of range." << endl;
        return false;
    }
    // check if place not filled
    uint row = cords / boardSize, column = cords % boardSize;
    if(board[row][column] != ' ') return false;
    return true;
}

bool TicTacToe::makeMove(uint cords){
    if(!isMvPsbl(cords)) return false;
    // check which player's turn
    uint row = cords / boardSize, column = cords % boardSize;
    char sign;
    if(turn == true){
        sign = 'X';
    } else {
        sign = 'O';
    }
    board[row][column] = sign;
    // change player for next round
    turn = !turn;
    return true;
}

bool TicTacToe::Win(){
    // set TIE as default if board fully filled
    state = TIE;
    for(uint i = 0; i < boardSize; i++){
        for(uint j = 0; j < boardSize; j++){
            if(board[i][j] == ' '){
                state = NO_END; // still possible moves avaliable
                i = boardSize; // so we break out of outer loop
                break; // break out of this loop
            }
        }
    }
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

    // check diagonals reversed direction
    for(uint i = 0; i < boardSize - numToWin+1; i++){
        for(uint j = boardSize-1; j >= numToWin-1; j--){
            bool isWin = true;
            for(uint k = 0; k < numToWin; k++){
                if(board[i+k][j-k] != 'X'){
                    isWin = false;
                    break;
                }
            }
            if(isWin){
                state = WIN_X;
                return true;
            }
            isWin = true;
            for(uint k = 0; k < numToWin; k++){
                if(board[i+k][j-k] != 'O'){
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
    if(state == TIE) return true;
    return false;
}

uint TicTacToe::movesLeft(){
    uint counter = 0;
    for(uint i = 0; i < boardSize; i++){
        for(uint j = 0; j < boardSize; j++){
            if(board[i][j] == ' ') counter++;
        }
    }
    return counter;
}

uint TicTacToe::findBestMv(bool isMaxi){
    uint bestMv;
    int bestVal = -INF;
    if(!isMaxi) bestVal = INF;
    if(movesLeft() == boardSize*boardSize) return boardSize*boardSize/2;
    for(uint i = 0; i < boardSize; i++){
        for(uint j = 0; j < boardSize; j++){
            if(board[i][j] == ' '){
                board[i][j] = 'O';
                int depth = movesLeft();
                MAX_DEPTH = boardSize == 4 ? 10 : 0;
                MAX_DEPTH = numToWin > 3 ? 10 : 0;
                MAX_DEPTH = boardSize == 5 ? 5 : 0;
                MAX_DEPTH = boardSize == 6 ? 3 : 0;
                int currVal = minimax(*this , depth, -INF, INF, !isMaxi);
                board[i][j] = ' ';
                if(currVal > bestVal && isMaxi){
                    bestMv = boardSize*i + j;
                    bestVal = currVal;
                }
                if(currVal < bestVal && !isMaxi){
                    bestMv = boardSize*i + j;
                    bestVal = currVal;
                }
            }
        }
    }
    return bestMv;
}
int TicTacToe::evaluateBoard(){
    // call Win() to set correct state
    this->Win();
    switch(state){
        case WIN_X:
            return -100;
        case WIN_O:
            return 100;
        case TIE:
            return 0;
        case NO_END:
            return 0;
    }
}
int minimax(TicTacToe game, uint depth, int alpha, int beta, bool isMaxi){
    // check if recursion ends or at this board state game is finished
    if(depth == MAX_DEPTH || game.Win()){
        int result = game.evaluateBoard(), add = 0;
        if(game.state == WIN_O) add = depth;
        if(game.state == WIN_X) add = -depth;
        return result + add;
    }

    if(isMaxi){
        int maxEval = -INF;
        uint mv = 0; // to remeber last made mv and not duplicate
        bool mvUsed = false; // to indicate if in previous iteration mv was made
        for(uint i = 0; i < depth; i++){
            TicTacToe child = game;
            while(!child.isMvPsbl(mv) || mvUsed){ // check if mv can be made and hasn't been made before
                mv++; // go to nxt mv
                mvUsed = false; // set mv as not used
            }
            child.turn = false;
            child.makeMove(mv);
            mvUsed = true; // set mv as used
            int eval = minimax(child, depth-1, alpha, beta, false);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if(beta <= alpha) break;
        }
        return maxEval;
    }
    else{
        int minEval = INF;
        uint mv = 0;
        bool mvUsed = false;
        for(uint i = 0; i < depth; i++){
            TicTacToe child = game;
            while(!child.isMvPsbl(mv) || mvUsed){
                mv++;
                mvUsed = false;
            }
            child.turn = true;
            child.makeMove(mv);
            mvUsed = true;
            int eval = minimax(child, depth-1, alpha, beta, true);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if(beta <= alpha) break;
        }
        return minEval;
    }
}