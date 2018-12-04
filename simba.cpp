#include "simba.h"


//setters
void Simba::setBoard(string input) {
    int pos = 0;
    istringstream ss(input);
    while(getline(ss, board[pos], ',')) {
        pos = pos + 1;
    }

}

void Simba::setPlayer (string input) {
    player_color = input;
}

//getters
void Simba::getBoard() {
    for (int pos=0; pos < 80; pos++) {
        cout << "value: " << board[pos];
        cout << "\n";
    }
}