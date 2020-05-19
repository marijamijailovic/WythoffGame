#ifndef ALGEBRAIC_H
#define ALGEBRAIC_H

#include "algebraic.h"

Algebraic::Algebraic(int n, int a) : Recursive_and_Algebraic(n, a) {}

Algebraic::~Algebraic() {}

void Algebraic::p_positions()
{
  double alpha, beta;

  alpha = (2-_a+sqrt(_a*_a+4))/2;
  beta = alpha+_a;

  _A.push_back(0);
  _B.push_back(0);

  for(int i=1;i<_n;i++){
    _A.push_back(static_cast<int>(floor(alpha*i)));
    _B.push_back(static_cast<int>(floor(beta*i)));
  }
}

#endif
