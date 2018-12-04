#ifndef Simba_H
#define Simba_H
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Simba
{
    private:

    //board
    string board[80];
    string player_color;

    public:
    void setBoard(string input);
    void setPlayer(string input);
    void getBoard();
};
#endif