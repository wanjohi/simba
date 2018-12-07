#ifndef Simba_H
#define Simba_H
#include <string>
#include <sstream>
#include <iostream>
#include <regex>
#include <thread>
#include <future>
#include <algorithm> 

using namespace std;

class Simba
{
    private:
    
    string player_color;
    string opp_color;
    int best_move;
    int best_column;
    string best_color;

    public:
    string board[80];
    void setBoard(string input);
    void setPlayer(string input);
    void printBoard();
    string getPlayer();
    int checkMove(string test_board[80], int col);
    void play();
    bool isWin(string test_board[80], int pos, string player);
    int minMax(string game_board[80], int depth, string color, int pos, bool im_playing);
};
#endif