#ifndef Simba_H
#define Simba_H
#include <string>
#include <array>
#include <iostream>
#include <regex>
#include <thread>
#include <future>
#include <algorithm> 
#include <random>
#include <functional>
#include <unordered_map>

using namespace std;

class Simba
{
    private:
    int best_move;
    int best_column;
    string best_color;

    public:
    char opp_color;
    char player_color;
    array<char, 80> board;
    unordered_map<string, int> trans_table;
    void setBoard(string input);
    void setPlayer(string input);
    void printBoard();
    char getPlayer();
    int checkMove(int col);
    void play();
    bool boardFull();
    char isWin(int pos);
    int minMax(int depth, int pos, bool im_playing, int alpha, int beta);
};
#endif