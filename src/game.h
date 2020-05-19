#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <time.h>
#include <cmath>
#include <cstdlib>

using namespace std;

class Game
{
  public:
    Game(int n);
    ~Game();
    vector<int>& get_piles();
    virtual void strategy() = 0;

  protected:
    int _n;

  private:
    vector<int> _piles;
    int _piles0;
    int _piles1;
};

#endif
