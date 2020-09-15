#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <time.h>
#include <vector>

using namespace std;

class Game {
public:
  Game(int n);
  ~Game();
  vector<int> &get_piles();
  virtual void strategy() = 0;

protected:
  int _n;

private:
  vector<int> _piles;
  int _piles0;
  int _piles1;
};

#endif
