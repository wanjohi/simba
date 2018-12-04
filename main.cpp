#include "simba.h"


int main(int argc, char **argv) {

    Simba new_simba;
    new_simba.setBoard(argv[2]);
    new_simba.setPlayer(argv[1]);
    new_simba.getBoard();
    
    return 0;

}