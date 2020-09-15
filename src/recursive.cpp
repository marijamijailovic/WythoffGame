#include "recursive.h"

Recursive::Recursive(int n, int a) : Recursive_and_Algebraic(n, a) {}

Recursive::~Recursive() {}

void Recursive::p_positions() {
  _A.push_back(0);
  _B.push_back(0);

  vector<int>::size_type c_size = vector<int>::size_type(2 * _n + 1);
  _C.resize(c_size, 0);
  int last_mex_index = 1;
  for (int i = 1; i <= _n; i++) {
    int mex = get_min_positive(last_mex_index);
    last_mex_index = mex;
    _A.push_back(mex);
    int b = _A[vector<int>::size_type(i)] + _a * i;
    _B.push_back(b);
    _C[vector<int>::size_type(mex)] = mex;
    if (b <= 2 * _n) {
      _C[vector<int>::size_type(b)] = b;
    }
  }
}

int Recursive::get_min_positive(int last_mex_index) {
  auto it = find(_C.begin() + last_mex_index, _C.end(), 0);
  return static_cast<int>(distance(_C.begin(), it));
}
