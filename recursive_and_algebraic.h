#ifndef RECURSIVE_AND_ALGEBRAIC_H
#define RECURSIVE_AND_ALGEBRAIC_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

#include "game.h"

using namespace std;

class Recursive_and_Algebraic : public Game
{
  public:
    Recursive_and_Algebraic(int a);
    ~Recursive_and_Algebraic();
    void strategy();
    virtual void p_positions();
  private:
    void recursive_and_algebraic_game(vector<int>& piles);
    bool isCurrentStateP(vector<int>& piles);
    void reach_P_position(vector<int>& piles);
    void recursive_and_algebraic_strategy(vector<int>& piles, bool winner);
//    bool isMoveAllow(vector<int>& piles, int x, int y);
//    bool player_move(vector<int>& piles, bool winner);
//    bool computer_move(vector<int>& piles, bool winner);
//
  protected:
    int _a;
    vector<int> _A;
    vector<int> _B;
};

#endif
