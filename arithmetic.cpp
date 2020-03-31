#include "arithmetic.h"
#include "game_helper.h"

Arithmetic::Arithmetic(int a) : _a(a) {}

Arithmetic::~Arithmetic() {}

void Arithmetic::strategy()
{
  arithmetic_characterization_of_P_Position();
  arithmetic_game(get_piles());
}

void Arithmetic::arithmetic_characterization_of_P_Position()
{
  alpha_continued_fractions();
  p_q_numerations();
  p_system_calculation();
  q_system_calculation();
}

void Arithmetic::alpha_continued_fractions()
{
  _alpha.push_back(1);
  fill_n(back_inserter(_alpha), n, _a);
}

void Arithmetic::p_q_numerations()
{
  int __p = 1;
  int __q = 0;
  _p.push_back(1);
  _p.push_back(_alpha.at(1)*_p.at(0)+__p);
  _q.push_back(1);
  _q.push_back(_alpha.at(1)*_q.at(0)+__q);
  for(int i=2;i<=n;i++){
    _p.push_back(_alpha.at(i)*_p.at(i-1)+_p.at(i-2));
    _q.push_back(_alpha.at(i)*_q.at(i-1)+_q.at(i-2));
  }
}

void Arithmetic::p_system_calculation()
{
  int size = 0;
  for(int i = 1; i <= n; i++){
    int quotient = 0;
    int remainder = 0;
    auto it_p = find(_p.begin(), _p.end(), i);
    int index;
    //if the i is in the p, then initialize the vecor r with size zeors
    //example: i = 1, 1 is in p[0], r = {0}
    //         i = 3, 3 is in p[1], r = {0, 0}
    if(it_p != _p.end()){
      size++;
      index = distance(_p.begin(), it_p);
    }
    vector<int> r(size,0);
    quotient = i/_p.at(index);
    remainder = i%_p.at(index);
    r.at(0) = quotient;
    if(remainder != 0){
      copy_backward(_p_system[remainder].begin(), _p_system[remainder].end(), r.end());
    }
    _p_system.insert(pair<int,vector<int>>(i, r));
  }
}

void Arithmetic::q_system_calculation()
{
  int size = 0;
  for(int i = 1; i <= n; i++){
    int quotient = 0;
    int remainder = 0;
    auto it_q = find(_q.begin(), _q.end(), i);
    int index;
    //if the i is in the q, then initialize the vecor r with size zeors
    //example: i = 1, 1 is in q[0], r = {0}
    //         i = 3, 3 is in q[1], r = {0, 0}
    if(it_q != _q.end()){
      size++;
      index = distance(_q.begin(), it_q);
    }
    vector<int> r(size,0);
    quotient = i/_q.at(index);
    remainder = i%_q.at(index);
    r.at(0) = quotient;
    if(remainder != 0){
      copy_backward(_q_system[remainder].begin(), _q_system[remainder].end(), r.end());
    }
    _q_system.insert(pair<int,vector<int>>(i, r));
  }
}

int Arithmetic::p_interpretation(vector<int>& R)
{
  auto it = find_if(_p_system.begin(), _p_system.end(), [& R] (auto i) {
    return R.size() == i.second.size() && equal(R.begin(), R.end(), i.second.begin());
  });
  return it->first;
}

void Arithmetic::arithmetic_game(vector<int>& piles)
{
  cout << "There is two piles of token : ";
  cout << "(" << piles.at(0) << ", " << piles.at(1) << ")" << endl;
  while(!Game_Helper::zeros_piles(piles)){
    cout << "Player turn ... " << endl;
    Game_Helper::player_move(piles,_a);
    if(Game_Helper::zeros_piles(piles)){
      break;
    }
    cout << "Computer turn ... " << endl; 
    if(piles.at(0) == 0 and piles.at(1) !=0) {
      Game_Helper::computer_move(piles,_a);
      if(Game_Helper::zeros_piles(piles)){
        break;
      }
    }
    arithmetic_strategy(piles);
    cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
  }
}

void Arithmetic::arithmetic_strategy(vector<int>& piles)
{
  vector<int> _Rp = _p_system.find(piles.at(0))->second;  
  int number_of_zeros_p = number_of_zeros_from_end(_Rp);

  if(number_of_zeros_p%2 != 0) {
    odd_number_of_zeros(piles,_Rp);
  }
  else {
    even_number_of_zeros(piles,_Rp);
  }
}

int Arithmetic::number_of_zeros_from_end(vector<int>& R)
{
  auto index = find_if(R.rbegin(), R.rend(), [] (int i) {
    return (i != 0);
  });

  return distance(R.rbegin(), index);
}

void Arithmetic::odd_number_of_zeros(vector<int>& piles, vector<int>& R)
{
  piles.at(1) = piles.at(0);
  R.pop_back();
  int _Ip = p_interpretation(R);
  piles.at(0) = _Ip;
}

void Arithmetic::even_number_of_zeros(vector<int>& piles, vector<int>& R)
{
  R.push_back(0);
  int _Ip = p_interpretation(R);
  if(piles.at(1) > _Ip) {
    piles.at(1) = _Ip;
  }
  else if(piles.at(1) < _Ip) {
    int d = abs(piles.at(1) - piles.at(0));
    int m = floor(d/_a);
    vector<int> _Rq = _q_system.find(m)->second;
    int number_of_zeros_q = number_of_zeros_from_end(_Rq);
    _Ip = p_interpretation(_Rq);
    if(number_of_zeros_q%2 != 0){
      piles.at(0) = _Ip - 1;
      piles.at(1) = _Ip - 1 + m*_a;
    }
    else {
      piles.at(0) = _Ip;
      piles.at(1) = _Ip + m*_a;
    }
  }
  else {
    Game_Helper::computer_move(piles,_a);
  }
}
