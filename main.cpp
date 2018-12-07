#include "simba.h"


int main(int argc, char **argv) {
    Simba new_simba;
    new_simba.setBoard(argv[2]);
    new_simba.setPlayer(argv[1]);
    //new_simba.isWin(new_simba.board,62,"r");
    
    int pos;
    int move_value = -1;
    int temp;
    int depth = 3;

    string color_to_play;
    int col_to_play;

    for(int col =0; col < 10; col++) {
        pos = new_simba.checkMove(new_simba.board,col);
        //cout <<"pos: " +to_string(pos) + "\n";
        if(pos > -1) {
            // play the players color
            auto f1 = async(&Simba::minMax, new_simba, new_simba.board, depth, argv[1], pos, false);
            //auto f2 = async(&Simba::minMax, new_simba, new_simba.board, depth, "g", pos, false);
            int val2 = new_simba.minMax(new_simba.board, depth, "g", pos, false);

            //f1.wait();
            //f2.wait();
            int val1 = f1.get();
            //int val2 = f2.get();
            //cout <<"val 1: " +to_string(val1) + "\n";
            //cout <<"val 2: " +to_string(val2) + "\n";

            if(val1 > move_value) {
                cout << "New best move found! " << to_string(col+1) << " has value: " << to_string(val1) << "\n";
                move_value = val1;
                color_to_play = argv[1];
                col_to_play = col;
            }

            if(val2 > move_value) {
                cout << "New best move found! " << to_string(col+1) << " has value: " << to_string(val2) << "\n";
                move_value = val2;
                color_to_play = "g";
                col_to_play = col;
            }
        } else {
            //new_simba.printBoard();
        }
    }

    cout << color_to_play + ","+ to_string(col_to_play + 1) + "\n";
    
    return 0;

}