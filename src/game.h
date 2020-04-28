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
    virtual void strategy() = 0;

  private:
    vector<int> _piles;
    int _piles0;
    int _piles1;
};

#endif
