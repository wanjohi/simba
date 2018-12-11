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
int Simba::checkMove(int col) {
    int free_pos;
    for(free_pos = 70; free_pos > -1 && board[free_pos + col] != "."; free_pos = free_pos - 10) {
        //cout << "Position " + to_string(free_pos + col) + " has: " + test_board[free_pos + col] + "\n"; 
    }

    // column is ful
    if(free_pos < 0) {
        return -1;
    }
    //cout << "Free space: " + to_string(free_pos + col) + "\n";

    return free_pos + col;

}

string Simba::isWin(int pos) {
    string match_string;
    regex winner_b("bbgg|ggbb|bgbg|gbgb|bggb|gbbg");
    regex winner_r("rrgg|ggrr|rgrg|grgr|rggr|grrg");

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
    //for(int i=0; (pos%10)-i>=0 && i<4; i++) far_left = i;
    // find how far right to go
    //for(int i=0; (pos%10)+i<=9 && i<4; i++) far_right = i;

    // check horizontal
    far_left = (pos/10)*10;
    test_string = "";
    for(int i=far_left; i <= far_left+9; i++) {
        test_string = test_string + board[i];
    }
    //cout << test_string + "\n";
    if(regex_search(test_string,winner_b)) {
       // cout << "win b: " + test_string + "\n";
        return "b";
    }
    if(regex_search(test_string,winner_r)) {
        //cout << "win r: " + test_string + "\n";
        return "r";
    }

    // find how far up to go
    //for(int i=0; i<4 && pos - (i*10) >= 0; i++) far_up = i;
    // find how far down to go
    //for(int i=0; i<4 && pos + (i*10) < 80; i++) far_down = i;
    far_up = pos % 10;

    //check vertical
    test_string = "";
    for(int i=far_up; i <= far_up + 70; i=i+10) {
        test_string = test_string + board[i];
    }
    //cout << test_string + "\n";
    if(regex_search(test_string,winner_b)) {
        //cout << "win b: " + test_string + "\n";
        return "b";
    }
    if(regex_search(test_string,winner_r)) {
        //cout << "win r: " + test_string + "\n";
        return "r";
    }

    // find how far diag up backward
    for(int i=0; i<4 && (pos-(i*11))%10 <= pos%10 && pos-(i*11) > 0; i++) far_diag_ub = i;
    // find how far diag down forward
    for(int i=0; i<4 && (pos+(i*11))%10 >= pos%10 && pos+(i*11) < 80; i++) far_diag_df = i;

    //check diagonal foward
    test_string = "";
    for(int i=pos-(far_diag_ub*11); i <= pos+(far_diag_df*11); i=i+11) {
        test_string = test_string + board[i];
    }
    //cout << test_string + "\n";
    if(regex_search(test_string,winner_b)) {
       // cout << "win b: " + test_string + "\n";
        return "b";
    }
    if(regex_search(test_string,winner_r)) {
        //cout << "win r: " + test_string + "\n";
        return "r";
    }

    // find how far diag up forward
    for(int i=0; i<4 && (pos-(i*9))%10 >= pos%10 && pos-(i*9) > 0; i++) far_diag_uf = i;
    // find how far diag down backward
    for(int i=0; i<4 && (pos+(i*9))%10 <= pos%10 && pos+(i*9) < 80; i++) far_diag_db = i;

    //check diagonal foward
    test_string = "";
    for(int i=pos-(far_diag_uf*9); i <= pos+(far_diag_db*9); i=i+9) {
        test_string = test_string + board[i];
    }
    //cout << test_string + "\n";
    if(regex_search(test_string,winner_b)) {
       // cout << "win b: " + test_string + "\n";
        return "b";
    }
    if(regex_search(test_string,winner_r)) {
        //cout << "win r: " + test_string + "\n";
        return "r";
    }

    

    return "";

}

bool Simba::boardFull() {
    for(int i=0; i<10; i++) {
        if(board[i] == ".") {
            return false;
        }
    }
    //cout << "board is full \n";
    return true;
}

int Simba::minMax(int depth, int pos, bool im_playing, int alpha, int beta) {

    int move_value;
    int temp;

    // if we are past our depth, return
    if(depth <=0) return 0;
    // Check for a winner
    string winner = Simba::isWin(pos);
    if(winner == player_color) return depth;
    if(winner == opp_color) return -depth;
    if(boardFull()) return 0;
    //cout << "at depth: " + to_string(depth) + "\n";
    
        
    
    move_value = im_playing?-10:10;

    for( int col=5; col < 10; col++) {
        pos = Simba::checkMove(col);
        //cout << "col: " + to_string(col) + "\n";
        if(pos > -1) {

            // play the players color
            board[pos] = im_playing? player_color: opp_color;
            temp = Simba::minMax(depth-1, pos, !im_playing, alpha, beta);
            move_value = im_playing? max(temp,move_value) : min(temp, move_value);
            im_playing? alpha = max(temp,alpha) : beta = min(temp,beta) ;

            // if(beta <= alpha) {
            //     //cout << "pruning: " + to_string(beta) + " | " + to_string(alpha) + "\n";
            //     board[pos] = ".";
            //     break;
            // }

            // play the neutral color
            board[pos] = "g";
            temp = Simba::minMax(depth-1, pos, !im_playing, alpha, beta);
            move_value = im_playing? max(temp,move_value) : min(temp, move_value);
            im_playing? alpha = max(temp,alpha) : beta = min(temp,beta) ;

            if(beta <= alpha) {
                //cout << "pruning: " + to_string(beta) + " | " + to_string(alpha) + "\n";
                board[pos] = ".";
                return move_value;
            }

            board[pos] = ".";
            
        }
    }

    for( int col=4; col > 0; col--) {
        pos = Simba::checkMove(col);
        //cout << "col: " + to_string(col) + "\n";
        if(pos > -1) {

            // play the players color
            board[pos] = im_playing? player_color: opp_color;
            temp = Simba::minMax(depth-1, pos, !im_playing, alpha, beta);
            move_value = im_playing? max(temp,move_value) : min(temp, move_value);
            im_playing? alpha = max(temp,alpha) : beta = min(temp,beta) ;

            // if(beta <= alpha) {
            //     //cout << "pruning: " + to_string(beta) + " | " + to_string(alpha) + "\n";
            //     board[pos] = ".";
            //     break;
            // }

            // play the neutral color
            board[pos] = "g";
            temp = Simba::minMax(depth-1, pos, !im_playing, alpha, beta);
            move_value = im_playing? max(temp,move_value) : min(temp, move_value);
            im_playing? alpha = max(temp,alpha) : beta = min(temp,beta) ;

            if(beta <= alpha) {
                //cout << "pruning: " + to_string(beta) + " | " + to_string(alpha) + "\n";
                board[pos] = ".";
                return move_value;
            }

            board[pos] = ".";
            
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