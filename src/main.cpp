#include "tic_tac_toe.hh"

using namespace std;

#define LOG(x) cout << x <<endl;

int main(){
    uint boardSize;
    bool playComp, whoStart;
    char choice;
    uint numOfSym;

    LOG("Type the size of the board you want to play on:");
    cin >> boardSize;

    LOG("Choose the number of symbols in a row for a win:");
    cin >> numOfSym;

    do{
        LOG("Do you want to play with computer or another player?");
        cin >> choice;
    }while(choice != 'y' | choice != 'n');
    playComp = (choice == 'y');

    do{
        LOG("Who starts? You or the other player/computer?");
        cin >> choice;
    }while(choice != 'y' | choice != 'n');
    whoStart = (choice == 'y');

    TicTacToe game(boardSize, numOfSym, whoStart, playComp);
    
    return 0;
}