#ifndef GAME_HELPER_H
#define GAME_HELPER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

class Game_Helper
{
  public:
    Game_Helper();
    ~Game_Helper();
    static bool zeros_piles(vector<int>& piles);
    static void player_move(vector<int>& piles, int a);
    static void computer_move(vector<int>& piles, int a);
  private:
    static bool try_to_win(vector<int>& piles, int a);
    static bool isMoveAllow(vector<int>& piles, int a, int x, int y);
 
};

#endif
