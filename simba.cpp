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

// Play move
int Simba::checkMove(int col) {
    int free_pos;

    for(free_pos = 70; board[free_pos + col] != "." && free_pos > -10; free_pos -= 10) {
        cout << "Position " + to_string(free_pos + col) + " has: " + board[free_pos + col] + "\n"; 
    }

    // column is ful
    if(free_pos < 0) {
        return -1;
    }
    cout << "Free space: " + to_string(free_pos + col) + "\n";

    return free_pos + col;

}

bool Simba::isWin(int pos, string color) {
    board[pos] = color;
    regex winner("");
    if(player_color == "b") {
        regex winner("bbgg|ggbb|bgbg|gbgb|bggb|gbbg");
    } else{
        regex winner("rrgg|ggrr|rgrg|grgr|rggr|grrg");
    }

    //check up
    if(pos > 29) {
        string test_string = board[pos] + board[pos-10] + board[pos-20] + board[pos-30];
        if(regex_match(test_string,winner)) return true;
    }

    // check down
    if(pos < 49) {
        string test_string = board[pos] + board[pos+10] + board[pos+20] + board[pos+30];
        if(regex_match(test_string,winner)) return true;
    }

    // check diagonal forward up
    if(pos > 29 && (pos % 10 < 10 - 3)) {
        string test_string = board[pos] + board[pos-9] + board[pos-18] + board[pos-27];
        if(regex_match(test_string,winner)) return true;
    }

    // check diagonal forward down
    if(pos < 49 && (pos % 10 < 10 - 3)) {
        string test_string = board[pos] + board[pos+9] + board[pos+18] + board[pos+27];
        if(regex_match(test_string,winner)) return true;
    }

    // check diagonal forward up
    if(pos > 29 && (pos % 10 < 3)) {
        string test_string = board[pos] + board[pos-9] + board[pos-18] + board[pos-27];
        if(regex_match(test_string,winner)) return true;
    }

    // check diagonal backward down
    if(pos < 29 && (pos % 10 < 3)) {
        string test_string = board[pos] + board[pos+9] + board[pos+18] + board[pos+27];
        if(regex_match(test_string,winner)) return true;
    }

    return false;

}

void Simba::play() {
    int pos;
    int last_pos;
    for(int col =0; col < 10; col++) {
        pos = Simba::checkMove(col);
        if(pos > -1) {
            last_pos = col;
            if(Simba::isWin(pos,"g")) {
                cout << "g," + to_string(col + 1) + "\n";
                return;
            }
            if(Simba::isWin(pos,player_color)) {
                cout << player_color + "," + to_string(col + 1) + "\n";
                return;
            }
        }
    }
    cout << player_color + ","+ to_string(last_pos + 1) + "\n";
}