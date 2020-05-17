#include "recursive.h"

Recursive::Recursive(int n, int a) : Recursive_and_Algebraic(n, a) {}

Recursive::~Recursive() {}

void Recursive::p_positions()
{
  _A.push_back(0);
  _B.push_back(0);
  _map[0] = 0;

  for(int i=1;i<_n;i++){
    int mex = get_min_positive();
    _A.push_back(mex);
    int k = _A.at(vector<int>::size_type(i))+_a*i;
    _B.push_back(k);
    _map[mex] = mex;
    _map[k] = k;
  }
}

int Recursive::get_min_positive()
{
  vector<int>::size_type index = 1;
  while(1){
    if(_map.find(static_cast<int>(index)) == _map.end()){
      return static_cast<int>(index);
    }
    index++;
  }
}
