#ifndef RECURSIVE_AND_ALGEBRAIC_H
#define RECURSIVE_AND_ALGEBRAIC_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#include "game.h"

using namespace std;

class Recursive_and_Algebraic : public Game {
public:
  Recursive_and_Algebraic(int n, int a);
  ~Recursive_and_Algebraic();
  void strategy();
  virtual void p_positions() = 0;

private:
  void recursive_and_algebraic_game(vector<int> &piles);
  void reach_P_position(vector<int> &piles);

protected:
  int _a;
  vector<int> _A;
  vector<int> _B;
};

#endif
