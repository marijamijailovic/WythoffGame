#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <time.h>
#include <cmath>

using namespace std;

class Game
{
  public:
    static const int n = 100;
    Game();
    ~Game();

    vector<int>& get_piles();
    virtual void strategy();
    //Think about to make a class P_positions : Game
    // void recursive_characterizaton_of_P_Position();
    // void algebraic_characterization_of_P_Position();
    // void arithmetic_characterization_of_P_Position();

  private:
    //void get_min_positive(vector<int>& A, const vector<int>& B);

    vector<int> _piles;
    int _piles0;
    int _piles1;
};

#endif
