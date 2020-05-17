#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include "recursive_and_algebraic.h"

using namespace std;

class Algebraic : public Recursive_and_Algebraic
{
  public:
    Algebraic(int n, int a);
    ~Algebraic();
    void p_positions();
};
