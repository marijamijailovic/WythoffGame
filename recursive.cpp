#include "recursive.h"

Recursive::Recursive(int a) : Recursive_and_Algebraic(a) {}

Recursive::~Recursive() {}

void Recursive::p_positions()
{
  _A.push_back(0);
  _B.push_back(0);

  for(int i=1;i<n;i++){
    get_min_positive();
    _B.push_back(_A.at(i)+_a*i);
  }
}

void Recursive::get_min_positive()
{
  //merge A and B in sort order and find the missing pos number
  set<int> C;

  C.insert(_A.begin(),_A.end());
  C.insert(_B.begin(),_B.end());

  int mex = 0;
  for(auto c : C){
    if(c != mex){
      break;
    }
    mex++;
  }
  _A.push_back(mex);
}
