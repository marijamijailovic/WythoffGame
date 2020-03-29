#ifndef GAME_HELPER_H
#define GAME_HELPER_H

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Game_Helper
{
  public:
    Game_Helper();
    ~Game_Helper();
    static bool isMoveAllow(vector<int>& piles, int a, int x, int y);
    static bool player_move(vector<int>& piles, int a, bool winner);
    static bool computer_move(vector<int>& piles, int a, bool winner);
};

#endif
