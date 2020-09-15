#include "recursive_and_algebraic.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Algebraic : public Recursive_and_Algebraic {
public:
  Algebraic(int n, int a);
  ~Algebraic();
  void p_positions();
};
