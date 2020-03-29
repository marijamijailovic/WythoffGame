#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

#include "game.h"

using namespace std;

class Arithmetic : public Game
{
  public:
    Arithmetic(int a);
    ~Arithmetic();
    void strategy();
  private:
    void arithmetic_characterization_of_P_Position();
    void alpha_continued_fractions();
    void p_q_numerations();
    void p_system_calculation();
    void q_system_calculation();
    int p_interpretation(vector<int>& R);
    void arithmetic_game(vector<int>& piles);
    void arithmetic_strategy(vector<int>& piles,bool winner);

    // void recursive_and_algebraic_game();
    // bool isCurrentStateP(vector<int>& piles);
    // void reach_P_position(vector<int>& piles);
    // void recursive_and_algebraic_strategy(vector<int>& piles, bool winner);
    // bool isMoveAllow(vector<int>& piles, int x, int y);
    // bool player_move(vector<int>& piles, bool winner);
    // bool computer_move(vector<int>& piles, bool winner);

    int _a;
    vector<int> _alpha;
    vector<unsigned long long int> _p;
    vector<unsigned long long int> _q;
    map<int,vector<int>> _p_system;
    map<int, vector<int>> _q_system;
};

#endif
