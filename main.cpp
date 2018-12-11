#include "simba.h"


int main(int argc, char **argv) {
    Simba new_simba1;
    Simba new_simba2;
    new_simba1.setBoard(argv[2]);
    new_simba1.setPlayer(argv[1]);
    new_simba2.setBoard(argv[2]);
    new_simba2.setPlayer(argv[1]);
    //new_simba.board[75] = "b";
   // new_simba.isWin(new_simba.board,75,"b");
   //cout << "player color: " + new_simba.opp_color + "\n";
    
    int pos;
    int move_value = -10;
    int temp;
    int depth = 4;
    string color_to_play;
    int col_to_play;
    //srand(time(NULL));
    auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());

    for(int col =0; col < 10; col++) {
        pos = new_simba1.checkMove(col);
        //cout <<"pos: " +to_string(pos) + "\n";
        if(pos > -1) {
            new_simba1.board[pos] = new_simba1.player_color;
            int val1 = new_simba1.minMax(depth, pos, false,-1000,1000);

            new_simba2.board[pos] = "g";
            int val2 = new_simba2.minMax(depth, pos, false,-1000,1000);

            //cout << "val1 " + to_string(val1) + "\n";
            //cout << "val2 " + to_string(val2) + "\n";

            // randomizer
            if(val1 == move_value && val2 == move_value && gen()) {
                cout << "Randomizing move! " << to_string(col+1) << " has value: " << to_string(val1) << "\n";
                move_value = val1;
                color_to_play = new_simba1.player_color;
                col_to_play = col +1;
            } else {
                if(val1 > move_value) {
                    cout << "New best move found! " << to_string(col+1) << " has value: " << to_string(val1) << "\n";
                    move_value = val1;
                    color_to_play = new_simba1.player_color;
                    col_to_play = col +1;
                }

                if(val2 > move_value) {
                    cout << "New best move found! " << to_string(col+1) << " has value: " << to_string(val2) << "\n";
                    move_value = val2;
                    color_to_play = "g";
                    col_to_play = col + 1;
                }
            }

            new_simba1.board[pos] = ".";
            new_simba2.board[pos] = ".";
        } else {
            //new_simba.printBoard();
        }
    }

    cout << color_to_play + ","+ to_string(col_to_play) + "\n";
    
    return 0;

}
