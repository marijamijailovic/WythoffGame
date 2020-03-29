#ifndef ALGEBRAIC_H
#define ALGEBRAIC_H

#include "algebraic.h"

Algebraic::Algebraic(int a) : Recursive_and_Algebraic(a) {}

Algebraic::~Algebraic() {}

void Algebraic::p_positions()
{
  double alpha, beta;

  alpha = (2-_a+sqrt(_a*_a+4))/2;
  beta = alpha+_a;
  cout << "TEST " << alpha << " " << beta << endl;
  _A.push_back(0);
  _B.push_back(0);

  //TODO change to C++ for_each
  for(int i=1;i<n;i++){
    _A.push_back(floor(i*alpha));
    _B.push_back(floor(i*beta));
  }

  cout << "P Algebraic Table " << endl;
  cout << "A " << endl;
  for_each(_A.begin(),_A.end(),[](int i){cout << i << " ";});
  cout << endl;
  cout << "B " << endl;
  for_each(_B.begin(),_B.end(),[](int i){cout << i << " ";});
  cout << endl;
}

#endif
