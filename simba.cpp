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

    if(player_color == "b") {
        opp_color = "r";
    } else {
        opp_color = "b";
    }
}

//getters
void Simba::printBoard() {
    for (int pos=0; pos < 80; pos++) {
        cout << "value: " << board[pos];
        cout << "\n";
    }
}

string Simba::getPlayer() {
    return player_color;
}

// Play move
int Simba::checkMove(string test_board[80], int col) {
    int free_pos;
    for(free_pos = 70; test_board[free_pos + col] != "." && free_pos > -1; free_pos = free_pos - 10) {
        //cout << "Position " + to_string(free_pos + col) + " has: " + test_board[free_pos + col] + "\n"; 
    }

    // column is ful
    if(free_pos < 0) {
        return -1;
    }
    //cout << "Free space: " + to_string(free_pos + col) + "\n";

    return free_pos + col;

}

bool Simba::isWin(string test_board[80], int pos, string player) {
    string match_string;
    if(player == "b") {
        match_string = "bbgg|ggbb|bgbg|gbgb|bggb|gbbg";
    } else{
        match_string = "rrgg|ggrr|rgrg|grgr|rggr|grrg";
    }
    regex winner(match_string);

    string test_string;
    int far_left = 0;
    int far_right = 0;
    int far_up = 0;
    int far_down = 0;
    int far_diag_uf = 0;
    int far_diag_df = 0;
    int far_diag_ub = 0;
    int far_diag_db = 0;

    // find how far left to go
    for(int i=0; (pos%10)-i>=0 && i<4; i++) far_left = i;
    // find how far right to go
    for(int i=0; (pos%10)+i<=9 && i<4; i++) far_right = i;

    // check horizontal
    test_string = "";
    for(int i=pos-far_left; i <= pos+far_right; i++) {
        test_string = test_string + test_board[i];
    }
    if(regex_search(test_string,winner)) {
        return true;
    }

    // find how far up to go
    for(int i=0; i<3 && pos - (i*10) >= 0; i++) far_up = i;
    // find how far down to go
    for(int i=0; i<3 && pos + (i*10) < 80; i++) far_down = i;

    //check vertical
    test_string = "";
    for(int i=pos-(far_up*10); i < pos+(far_down*10); i=i+10) {
        test_string = test_string + test_board[i];
    }
    if(regex_search(test_string,winner)) {
        return true;
    }

    // find how far diag up backward
    for(int i=0; i<3 && (pos-(i*11))%10 <= pos%10 && pos-(i*11) > 0; i++) far_diag_ub = i;
    // find how far diag down forward
    for(int i=0; i<3 && (pos+(i*11))%10 >= pos%10 && pos+(i*11) < 80; i++) far_diag_df = i;

    //check diagonal foward
    test_string = "";
    for(int i=pos-(far_diag_ub*11); i <= pos+(far_diag_df*11); i=i+11) {
        test_string = test_string + test_board[i];
    }
    if(regex_search(test_string,winner)) {
        return true;
    }

    // find how far diag up forward
    for(int i=0; i<3 && (pos-(i*9))%10 >= pos%10 && pos-(i*11) > 0; i++) far_diag_uf = i;
    // find how far diag down backward
    for(int i=0; i<3 && (pos+(i*9))%10 <= pos%10 && pos+(i*11) < 80; i++) far_diag_db = i;

    //check diagonal foward
    test_string = "";
    for(int i=pos-(far_diag_uf*9); i <= pos+(far_diag_db*9); i=i+9) {
        test_string = test_string + test_board[i];
    }
    if(regex_search(test_string,winner)) {
        return true;
    }

    

    return false;

}

int Simba::minMax(string game_board[80],int depth, string color, int pos, bool im_playing) {

    int move_value;
    int temp = 0;
    string color_to_play;
    string test_board[80];

    // if we are past our depth, return
    if(depth <=0) {
        return 0;
    }
    // play the move
    copy(game_board, game_board + sizeof(game_board[80]), test_board);
    test_board[pos] = color;

    // check if we lost
        if(Simba::isWin(test_board, pos, opp_color)) {
            //cout << "losing move\n";
            return -depth;
        }

    //check if we won
        if(Simba::isWin(test_board, pos, player_color)) {
            //cout << "winning move\n";
            return depth;
        }
        
    
    move_value = im_playing?-1:1;

    for( int col=0; col < 10; col++) {
        pos = Simba::checkMove(test_board, col);
        if(pos > -1) {
            // play the move
            color_to_play = im_playing? player_color: opp_color;

            // play the players color
            temp = Simba::minMax(test_board, depth-1, color_to_play, pos, !im_playing);
            if(temp > move_value) {
                //cout << "New best move found! " << to_string(col+1) << " has value: " << to_string(temp) << "\n";
                move_value = temp;
            }
            

            // play the neutral color
            temp = Simba::minMax(test_board, depth-1, "g", pos, !im_playing);
            if(temp > move_value) {
                //cout << "New best move found! " << to_string(col+1) << " has value: " << to_string(temp) << "\n";
                move_value = temp;
            }
        }
    }

    return move_value;

}

void Simba::play() {
    // int pos;
    // int move_value = -1;
    // int temp;
    // int depth = 3;

    // string color_to_play;
    // int col_to_play;

    // for(int col =0; col < 10; col++) {
    //     pos = Simba::checkMove(col);
    //     if(pos > -1) {
    //         // play the move
    //         board[pos] = player_color;
    //         // play the players color
    //         thread t1(this.minmax, this, "Sample Task");
    //         thread t1(Simba::minMax(depth, pos, false),depth,pos,false);
    //         temp = Simba::minMax(depth, pos, false);
    //         if(temp > move_value) {
    //             cout << "New best move found! " << to_string(col+1) << " has value: " << to_string(temp) << "\n";
    //             move_value = temp;
    //             color_to_play = player_color;
    //             col_to_play = col;
    //         }

    //         // play the move
    //         board[pos] = "g";
    //         // play the neutral color
    //         thread t2(Simba::minMax(depth, pos, false));
    //         temp = Simba::minMax(depth, pos, false);
    //         if(temp > move_value) {
    //             cout << "New best move found! " << to_string(col+1) << " has value: " << to_string(temp) << "\n";
    //             move_value = temp;
    //             color_to_play = "g";
    //             col_to_play = col;
    //         }
    //         // reset the board
    //         board[pos] = ".";
    //     }
    // }
    // cout << color_to_play + ","+ to_string(col_to_play + 1) + "\n";
}