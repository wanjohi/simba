#ifndef Simba_H
#define Simba_H
#include <string>
#include <sstream>
#include <iostream>
#include <regex>
#include <thread>
#include <future>
#include <algorithm> 
#include <random>
#include <time.h>

using namespace std;

class Simba
{
    private:
    int best_move;
    int best_column;
    string best_color;

    public:
    string opp_color;
    string player_color;
    string board[80];
    void setBoard(string input);
    void setPlayer(string input);
    void printBoard();
    string getPlayer();
    int checkMove(int col);
    void play();
    bool boardFull();
    string isWin(int pos);
    int minMax(int depth, int pos, bool im_playing, int alpha, int beta);
};
#endif