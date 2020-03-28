#include "arithmetic_strategy.h"

void alpha_continued_fractions(vector<int>& alpha, int a, int n)
{
  alpha.push_back(1);
  fill_n(back_inserter(alpha), n, a);
}

void p_q_numerations(vector<unsigned long long int>& p, vector<unsigned long long int>& q, const vector<int>& alpha, int n)
{
  int _p = 1;
  int _q = 0;
  //TODO to C++ style, and smarter
  p.push_back(1);
  p.push_back(alpha.at(1)*p.at(0)+_p);
  q.push_back(1);
  q.push_back(alpha.at(1)*q.at(0)+_q);
  //ubaci jos n elemenata od 2gog
  for(int i=2;i<=n;i++){
    p.push_back(alpha.at(i)*p.at(i-1)+p.at(i-2));
    q.push_back(alpha.at(i)*q.at(i-1)+q.at(i-2));
  }

}

void p_system_calculation(map<int, vector<int>>& p_system, const vector<unsigned long long int>& p, int n)
{
  int size = 0;
  for(int i = 1; i <= n; i++){
    int quotient = 0;
    int remainder = 0;
    auto it_p = find(p.begin(), p.end(), i);
    int index;
    //if the i is in the p, then initialize the vecor r with size zeors
    //example: i = 1, 1 is in p[0], r = {0}
    //         i = 3, 3 is in p[1], r = {0, 0}
    if(it_p != p.end()){
      size++;
      index = distance(p.begin(), it_p);
    }
    vector<int> r(size,0);
    quotient = i/p.at(index);
    remainder = i%p.at(index);
    r.at(0) = quotient;
    if(remainder != 0){
      copy_backward(p_system[remainder].begin(), p_system[remainder].end(), r.end());
    }

    p_system.insert(pair<int,vector<int>>(i, r));
  }
}

void q_system_calculation(map<int, vector<int>>& q_system, const vector<unsigned long long int>& q, int n)
{
  int size = 0;
  for(int i = 1; i <= n; i++){
    int quotient = 0;
    int remainder = 0;
    auto it_q = find(q.begin(), q.end(), i);
    int index;
    //if the i is in the q, then initialize the vecor r with size zeors
    //example: i = 1, 1 is in q[0], r = {0}
    //         i = 3, 3 is in q[1], r = {0, 0}
    if(it_q != q.end()){
      size++;
      index = distance(q.begin(), it_q);
    }
    vector<int> r(size,0);
    quotient = i/q.at(index);
    remainder = i%q.at(index);
    r.at(0) = quotient;
    if(remainder != 0){
      copy_backward(q_system[remainder].begin(), q_system[remainder].end(), r.end());
    }

    q_system.insert(pair<int,vector<int>>(i, r));
  }
}

int p_interpretation(const map<int,vector<int>>& p_system, vector<int>& R)
{
  auto it = find_if(p_system.begin(), p_system.end(), [& R] (auto i) {
    return R.size() == i.second.size() && equal(R.begin(), R.end(), i.second.begin());
  });
  return it->first;
}

void arithmetic_game(const map<int,vector<int>>& p_system, const map<int,vector<int>>& q_system, vector<int>& piles, int a, int n)
{
  bool winner = false;
  while(!winner){
    winner = player_move(piles,a,winner);
    if(winner){
      break;
    }
    winner = computer_move(piles,a,winner);
    if(winner){
      break;
    }
    arithmetic_strategy(p_system,q_system,piles,a,n,winner);
    cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
  }
}

void arithmetic_strategy(const map<int,vector<int>>& p_system, const map<int,vector<int>>& q_system, vector<int>& piles, int a, int n, bool winner)
{
  int computer_x, computer_y;

  vector<int> _Rp = p_system.find(piles.at(0))->second;
  auto index_p = find_if(_Rp.rbegin(), _Rp.rend(), [] (int i) {
    return (i != 0);
  });

  int number_of_zeros_p = distance(_Rp.rbegin(), index_p);

  if(number_of_zeros_p%2 != 0) {
    cout << "Neparan broj nula " << endl;
    piles.at(1) = piles.at(0);
    _Rp.pop_back();
    int _Ip = p_interpretation(p_system,_Rp);
    cout << "Ip " << _Ip << endl;
    piles.at(0) = _Ip;
  }
  else {
    cout << "Paran broj nula " << endl;
    _Rp.push_back(0);
    int _Ip = p_interpretation(p_system,_Rp);
    cout << "Ip " << _Ip << endl;
    if(piles.at(1) > _Ip) {
      piles.at(1) = _Ip;
    }
    else if(piles.at(1) == _Ip) {
      computer_x = rand()%piles.at(0);
	    computer_y = rand()%piles.at(1);

      while(!isMoveAllow(piles,computer_x,computer_y,a)){
        cout << "Move " << computer_x << ", " << computer_y << " is invalid, please try again!" << endl;
        computer_x = rand()%piles.at(0);
	      computer_y = rand()%piles.at(1);
      }

      piles.at(0) -= computer_x;
      piles.at(1) -= computer_y;
    }
    else {
      int d = abs(piles.at(1) - piles.at(0));
      int m = floor(d/a);
      cout << "TEST R_q reprezentacija od " << m << endl;
      vector<int> _Rq = q_system.find(m)->second;
      for_each(_Rq.begin(),_Rq.end(),[](int i) {cout << i << " ";});
      cout << endl;
      auto index_q = find_if(_Rq.rbegin(), _Rq.rend(), [] (int i) {
        return (i != 0);
      });
      int number_of_zeros_q = distance(_Rq.rbegin(),index_q);
      cout << "broj nula " << number_of_zeros_q;
      _Ip = p_interpretation(p_system,_Rq);
      cout << "Ip je " << endl;
      if(number_of_zeros_q%2 != 0){
        piles.at(0) = _Ip - 1;
        piles.at(1) = _Ip - 1 + m*a;
      }
      else {
        piles.at(0) = _Ip;
        piles.at(1) = _Ip + m*a;
      }
    }
  }
}
