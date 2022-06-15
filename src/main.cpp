#include "../inc/tic_tac_toe.hh"

using namespace std;

#define LOG(x) cout << x <<endl;

int main(){
    bool gameON = true;
    while(gameON){

        TicTacToe newGame = initialize_Game();
        newGame.startGame();

        char choice;
        do{
            LOG("Do you want to play again? (y/n)");
            cin >> choice;
        }while(choice != 'y' && choice != 'n');
        gameON = (choice == 'y');

    }
    return 0;
}