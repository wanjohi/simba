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
    int depth = 3;
    int alpha = -1000;
    int beta = 1000;
    string color_to_play;
    int col_to_play;
    //srand(time(NULL));
    auto gen = bind(std::uniform_int_distribution<>(0,1),default_random_engine());

    for(int col=4; col >= 0; col--) {
        // middle to left
        pos = new_simba1.checkMove((col +1)%10);
        //cout <<"pos: " +to_string(pos) + "\n";
        if(pos > -1) {
            // create thread
            new_simba2.board[pos] = 'g';
            auto f2 = async(&Simba::minMax, new_simba2, depth, pos, false,alpha,beta);

            new_simba1.board[pos] = new_simba1.player_color;
            int val1 = new_simba1.minMax(depth, pos, false,alpha,beta);

            int val2 = f2.get();


            // Play winning move stop wasting time
            if(val1 == depth) {
                cout << "New best move found! " << to_string(((col +1)%10)+1) << " has value: " << to_string(val1) << "\n";
                move_value = val1;
                color_to_play = new_simba1.player_color;
                col_to_play = ((col +1)%10) +1;
                break;
            } else if(val2 == depth) {
                cout << "New best move found! " << to_string(((col +1)%10)+1) << " has value: " << to_string(val2) << "\n";
                move_value = val2;
                color_to_play = "g";
                col_to_play = ((col +1)%10) + 1;
                break;
            }

            // randomizer
            if(val1 == move_value && val2 == move_value && gen()) {
                cout << "Randomizing move! " << to_string(((col +1)%10)+1) << " has value: " << to_string(val1) << "\n";
                move_value = val1;
                color_to_play = new_simba1.player_color;
                col_to_play = ((col +1)%10) +1;
            } else {
                if(val1 > move_value) {
                    cout << "New best move found! " << to_string(((col +1)%10)+1) << " has value: " << to_string(val1) << "\n";
                    move_value = val1;
                    color_to_play = new_simba1.player_color;
                    col_to_play = ((col +1)%10) +1;
                }

                if(val2 > move_value) {
                    cout << "New best move found! " << to_string(((col +1)%10)+1) << " has value: " << to_string(val2) << "\n";
                    move_value = val2;
                    color_to_play = "g";
                    col_to_play = ((col +1)%10) + 1;
                }
            }

            new_simba1.board[pos] = '.';
            new_simba2.board[pos] = '.';
        }

        // middle to right
        pos = new_simba1.checkMove((10 - col)%10);
        //cout <<"pos: " +to_string(pos) + "\n";
        if(pos > -1) {
            // create thread
            new_simba2.board[pos] = 'g';
            auto f2 = async(&Simba::minMax, new_simba2, depth, pos, false,alpha,beta);

            new_simba1.board[pos] = new_simba1.player_color;
            int val1 = new_simba1.minMax(depth, pos, false,alpha,beta);

            int val2 = f2.get();

            // Play winning move stop wasting time
            if(val1 == depth) {
                cout << "New best move found! " << to_string(((10 - col)%10)+1) << " has value: " << to_string(val1) << "\n";
                move_value = val1;
                color_to_play = new_simba1.player_color;
                col_to_play = ((10 - col)%10) +1;
                break;
            } else if(val2 == depth) {
                cout << "New best move found! " << to_string(((10 - col)%10)+1) << " has value: " << to_string(val2) << "\n";
                move_value = val2;
                color_to_play = "g";
                col_to_play = ((10 - col)%10) + 1;
                break;
            }

            // randomizer
            if(val1 == move_value && val2 == move_value && gen()) {
                cout << "Randomizing move! " << to_string(((10 - col)%10)+1) << " has value: " << to_string(val1) << "\n";
                move_value = val1;
                color_to_play = new_simba1.player_color;
                col_to_play = ((10 - col)%10) +1;
            } else {
                if(val1 > move_value) {
                    cout << "New best move found! " << to_string(((10 - col)%10)+1) << " has value: " << to_string(val1) << "\n";
                    move_value = val1;
                    color_to_play = new_simba1.player_color;
                    col_to_play = ((10 - col)%10) +1;
                }

                if(val2 > move_value) {
                    cout << "New best move found! " << to_string(((10 - col)%10)+1) << " has value: " << to_string(val2) << "\n";
                    move_value = val2;
                    color_to_play = "g";
                    col_to_play = ((10 - col)%10) + 1;
                }
            }

            new_simba1.board[pos] = '.';
            new_simba2.board[pos] = '.';
        }
    }

    cout << color_to_play + ","+ to_string(col_to_play) + "\n";
    
    return 0;

}
