#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "game.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class Arithmetic : public Game {
public:
  Arithmetic(int n, int a);
  ~Arithmetic();
  void strategy();
  void arithmetic_characterization_of_P_Position();

private:
  void alpha_continued_fractions();
  void p_q_numerations();
  void p_system_calculation();
  void q_system_calculation();
  int p_interpretation(vector<int> &R);
  void arithmetic_game(vector<int> &piles);
  void arithmetic_strategy(vector<int> &piles);
  void odd_number_of_zeros(vector<int> &piles, vector<int> &R);
  void even_number_of_zeros(vector<int> &piles, vector<int> &R);
  int number_of_zeros_from_end(vector<int> &R);

  int _a;
  vector<int> _alpha;
  vector<int> _p;
  vector<int> _q;
  map<int, vector<int>> _p_system;
  map<int, vector<int>> _q_system;
};

#endif
