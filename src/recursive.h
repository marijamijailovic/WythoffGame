#ifndef RECUSRSIVE_H
#define RECUSRSIVE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include "recursive_and_algebraic.h"

using namespace std;

class Recursive : public Recursive_and_Algebraic
{
  public:
    Recursive(int a);
    ~Recursive();
    void p_positions();

  private:
    void get_min_positive();
};

#endif
