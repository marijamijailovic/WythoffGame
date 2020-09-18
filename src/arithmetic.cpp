#include "arithmetic.h"
#include "game_helper.h"

Arithmetic::Arithmetic(int n, int a) : Game(n), _a(a) {}

Arithmetic::~Arithmetic() {}

void Arithmetic::strategy() {
  arithmetic_characterization_of_P_Position();
  arithmetic_game(get_piles());
}

void Arithmetic::arithmetic_characterization_of_P_Position() {
  alpha_continued_fractions();
  p_q_numerations();
  p_system_calculation();
  q_system_calculation();
}

void Arithmetic::alpha_continued_fractions() {
  _alpha.push_back(1);
  fill_n(back_inserter(_alpha), _n, _a);
}

void Arithmetic::p_q_numerations() {
  _p.push_back(1);
  _p.push_back(_alpha[1] * _p[0] + 1);
  _q.push_back(1);
  _q.push_back(_alpha[1] * _q[0] + 0);
  vector<int>::size_type index = 2;
  int memoize = _alpha[2] * _p[1] + _p[0];
  while (memoize <= _n) {
    memoize = _alpha[index] * _p[index - 1] + _p[index - 2];
    _p.push_back(memoize);
    _q.push_back(_alpha[index] * _q[index - 1] + _q[index - 2]);
    index++;
  }
}

void Arithmetic::p_system_calculation() {
  vector<int>::size_type size = 0;
  int index;
  for (int i = 1; i <= _n; i++) {
    // if the i is in the p, then initialize the vecor r with size zeros
    // example: i = 1, 1 is in p[0], r = {0}
    //         i = 3, 3 is in p[1], r = {0, 0}
    if (binary_search(_p.begin(), _p.end(), i)) {
      size++;
      index = i;
    }
    vector<int> r(size, 0);
    const int quotient = i / index;
    const int remainder = i % index;
    r[0] = quotient;
    if (remainder != 0) {
      copy_backward(_p_system[remainder].begin(), _p_system[remainder].end(),
                    r.end());
    }
    _p_system[i] = r;
  }
}

void Arithmetic::q_system_calculation() {
  vector<int>::size_type size = 0;
  int index;
  for (int i = 1; i <= _n; i++) {
    // if the i is in the q, then initialize the vecor r with size zeros
    // example: i = 1, 1 is in q[0], r = {0}
    //         i = 3, 3 is in q[1], r = {0, 0}
    if (binary_search(_q.begin(), _q.end(), i)) {
      size++;
      index = i;
    }
    vector<int> r(size, 0);
    const int quotient = i / index;
    const int remainder = i % index;
    r[0] = quotient;
    if (remainder != 0) {
      copy_backward(_q_system[remainder].begin(), _q_system[remainder].end(),
                    r.end());
    }
    _q_system[i] = r;
  }
}

int Arithmetic::p_interpretation(vector<int> &R) {
  auto it = find_if(_p_system.begin(), _p_system.end(), [&R](auto i) {
    return R.size() == i.second.size() &&
           equal(R.begin(), R.end(), i.second.begin());
  });
  return it->first;
}

void Arithmetic::arithmetic_game(vector<int> &piles) {
  cout << "There is two piles of token : ";
  cout << "(" << piles[0] << ", " << piles[1] << ")" << endl;
  while (!Game_Helper::zeros_piles(piles)) {
    cout << "Player turn ... " << endl;
    Game_Helper::player_move(piles, _a);
    if (Game_Helper::zeros_piles(piles)) {
      break;
    }
    cout << "Computer turn ... " << endl;
    if (piles[0] == 0 and piles[1] != 0) {
      Game_Helper::computer_move(piles, _a);
      if (Game_Helper::zeros_piles(piles)) {
        break;
      }
    }
    arithmetic_strategy(piles);
    cout << "Current state od piles is (" << piles[0] << ", " << piles[1] << ")"
         << endl;
  }
}

void Arithmetic::arithmetic_strategy(vector<int> &piles) {
  vector<int> _Rp = _p_system.find(piles[0])->second;
  int number_of_zeros_p = number_of_zeros_from_end(_Rp);

  if (number_of_zeros_p % 2 != 0) {
    odd_number_of_zeros(piles, _Rp);
  } else {
    even_number_of_zeros(piles, _Rp);
  }
}

int Arithmetic::number_of_zeros_from_end(vector<int> &R) {
  vector<int>::reverse_iterator index =
      find_if(R.rbegin(), R.rend(), [](int i) { return (i != 0); });

  int result = static_cast<int>(distance(R.rbegin(), index));

  return result;
}

void Arithmetic::odd_number_of_zeros(vector<int> &piles, vector<int> &R) {
  piles[1] = piles[0];
  R.pop_back();
  int _Ip = p_interpretation(R);
  piles[0] = _Ip;
}

void Arithmetic::even_number_of_zeros(vector<int> &piles, vector<int> &R) {
  R.push_back(0);
  int _Ip = p_interpretation(R);
  if (piles[1] > _Ip) {
    piles[1] = _Ip;
  } else if (piles[1] < _Ip) {
    int d = abs(piles[1] - piles[0]);
    int m = d / _a;
    vector<int> _Rq = _q_system.find(m)->second;
    int number_of_zeros_q = number_of_zeros_from_end(_Rq);
    _Ip = p_interpretation(_Rq);
    if (number_of_zeros_q % 2 != 0) {
      piles[0] = _Ip - 1;
      piles[1] = _Ip - 1 + m * _a;
    } else {
      piles[0] = _Ip;
      piles[1] = _Ip + m * _a;
    }
  } else {
    Game_Helper::computer_move(piles, _a);
  }
}
