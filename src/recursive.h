#ifndef RECUSRSIVE_H
#define RECUSRSIVE_H

#include "recursive_and_algebraic.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Recursive : public Recursive_and_Algebraic {
public:
  Recursive(int n, int a);
  ~Recursive();
  void p_positions();

private:
  vector<int> _C;
  int get_min_positive(int last_index);
};

#endif
