#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>
#include <set>
#include <time.h>
#include <cmath>

using namespace std;

void recursive_characterizaton_of_P_Position(vector<int>& piles, int n);
void algebraic_characterization_of_P_Position(vector<int>& piles, int n);
void alpha_continued_fractions(vector<int>& alpha, int a, int n);
void arithmetic_characterization_of_P_Position(vector<int>& piles, int n);
void p_q_numerations(vector<unsigned long long int>& p, vector<unsigned long long int>& q, const vector<int>& alpha, int n);
void p_system_calculation(map<int, vector<int>>& p_system, const vector<unsigned long long int>& p, int n);
void q_system_calculation(map<int, vector<int>>& q_system, const vector<unsigned long long int>& q, int n);
int p_interpretation(const map<int,vector<int>>& p_system, vector<int>& R); 
void get_min_positive(vector<int>& A, const vector<int>& B);
bool isMoveAllow(vector<int>& piles, int x, int y, int a);
bool isCurrentStateP(const vector<int>& A, const vector<int>& B, const vector<int>& piles);
void reach_P_position(const vector<int>& A, const vector<int>& B, vector<int>& piles, int a);
void init_game(vector<int>& piles, int n);
void game(const vector<int>& A, const vector<int>& B, vector<int>& piles, int a, int n);
void game_2(const map<int,vector<int>>& p_system, const map<int,vector<int>>& q_system, vector<int>& piles, int a, int n);
void recursive_and_algebraic_strategy(const vector<int>& A, const vector<int>& B, vector<int>& piles, int a, int n, bool winner);
void arithmetic_strategy(const map<int,vector<int>>& p_system, const map<int,vector<int>>& q_system, vector<int>& piles, int a, int n, bool winner);

int n = 100; 
vector<int> piles; 
int game_option;
 
int main()
{ 

  cout << "##########   WYTHOFF GAME  ##########" << endl;
  cout << "There three way how we can calculate P-Position table (please choose the one of the option)" << endl;
  cout << "1) Recursive characterization of the P-Positions" << endl;
  cout << "2) Algebraic characterization of the P-Positions" << endl;
  cout << "3) Arithmetic characterization of the P-Positions" << endl;

  cin >> game_option;
  
  switch(game_option) {
   case 1:
    //Recursive Characterization of the P-Positions
    //A_n = mex{A_i, B_i : i<n} -- mex najmanji nenegativan broj koji nije u A_n
    //mex{} = 0
    recursive_characterizaton_of_P_Position(piles,n);
    break;
   case 2:
    algebraic_characterization_of_P_Position(piles,n);
    break;
   case 3:
    arithmetic_characterization_of_P_Position(piles,n);
    break;
  }

  return 0; 
}

void reach_P_position(const vector<int>& A,const vector<int>& B, vector<int>& piles, int a)
{
  //two case:
  //I  : if piles(0) is B_n, save n, then x = piles(0) and y = A_n,
  //II : if piles(0) is A_n, save n, if y > B_n then y  = B_n
  //                                 if y < B_n, d = y -x, m = donji_ceo(d/a) then x = A_m, y = B_m, m < n  
  if(find(B.begin(), B.end(), piles.at(1)) != end(B)){
    //cout << "Prvi slucaj x je u B " << endl;
    //(47, 74)
    //piles_0 = 47, piles_1 = 74
    //piles_1 = piles_0
    //piles_0 = ono sto je na A poziciji koja odgovara onoj gde je B 47
    //(19, 47)
    auto it = find(B.begin(),B.end(), piles.at(0));
    int index = distance(B.begin(), it);
    piles.at(1) = piles.at(0);
    piles.at(0) = A.at(index);
  }
  else if(find(A.begin(), A.end(), piles.at(0)) != end(A)){
    auto it = find(A.begin(),A.end(), piles.at(0));
    int index = distance(A.begin(), it);
    if(piles.at(1) >= B.at(index)){
      //cout << "Prvi slucaj y je > B " << endl;
      //(19,74)
      //piles_0 = 19, piles_1 = 74
      //piles_0 = piles_0
      //piles_1 = ono sto je na B poziciji koja odgovvara onoj gde je A 19
      //computer_move.push_back(piles.at(0));
      //computer_move(B.at(find(index)));
      piles.at(1) = B.at(index);
    }
    else{
      int d = abs(piles.at(1) - piles.at(0));
      int m = floor(d/a);
      piles.at(0) = A.at(m);
      piles.at(1) = B.at(m);
    }
  }

}

bool isCurrentStateP(const vector<int>& A, const vector<int>& B, const vector<int>& piles)
{
  auto it_A = find(A.begin(), A.end(), piles.at(0));
  auto it_B = find(B.begin(), B.end(), piles.at(1));

  if(find(A.begin(), A.end(), piles.at(0)) != A.end() && find(B.begin(), B.end(), piles.at(1)) != B.end() && distance(A.begin(), it_A) == distance(B.begin(), it_B)) {
    return true;
  }
  return false;
}


bool isMoveAllow(vector<int>& piles, int x, int y, int a)
{
  if(piles.at(0) > piles.at(1)){
    return false;
  }

  if(x == 0 && y == 0){
    return false;
  } 

  if(piles.at(0) - x > piles.at(1) - y) {
    return false;
  }

  if(x > 0 && y > 0 && !(abs(x - y) < a)){
    return false;
  }

  if((piles.at(0) - x) < 0 || (piles.at(1) - y) < 0){
    return false;
  }

  return true;
}

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

void arithmetic_characterization_of_P_Position(vector<int>& piles, int n)
{
  int a;
  cout << "Please input a, a can be any positive integer " << endl;
  cin >> a;

  //continued fractions and systems of numeration
  //alpha is irrational 1<alpha<2

  vector<int> alpha;
  alpha_continued_fractions(alpha, a, n);
  
  vector<unsigned long long int> p;
  vector<unsigned long long int> q;
  p_q_numerations(p, q, alpha, n);

  map<int, vector<int>> p_system;
  map<int, vector<int>> q_system;

  p_system_calculation(p_system, p, n);
  q_system_calculation(q_system, q, n);

  //GAME PLAY

  //R = (dm, dm-1, ... d0)
  //R' = (dm, ..., d0, 0)
  //R'' = (dm, ... , d1)

  //FIRST CASE
  //p-representation(Rp(i)) ends with even num of zeros --> An
  //Bn = An+ an --> p-representation end with odd num of zeros

  //Rp(Bn) = R'(An) // 
  //Ip(Rq(i)) = An ---> Rq(i) ends with even num of zeros
  //Ip(Rq(i)) = An+1 ---> Rq(i) ends with odd num of zeros

  //GAME
  //curr position (x,y)
  //1) calculate Rp(x)
  //  --if it is end with odd num of zeros ---> x = Bk, end win move --> (x,y) = (Ip(Rp''(x)),x)
  //  --if it is end with even num of zeros ---> x = Ak, 
  //      * y > Ip(Rp'(x)) ---> (x,y) = (x, Ip(Rp'(x)) win move
  //      * y = Ip(Rp'(x)) ---> (x,y) is P , can't win from this pos
  //      * y < Ip(Rp'(x)) ---> m = [(y-x)/a]
  
  init_game(piles,n);
  game_2(p_system,q_system,piles,a,n);
}

int p_interpretation(const map<int,vector<int>>& p_system, vector<int>& R) 
{
  auto it = find_if(p_system.begin(), p_system.end(), [& R] (auto i) {
    return equal(R.begin(), R.end(), i.second.begin());
  });

  return it->first;
}

void algebraic_characterization_of_P_Position(vector<int>& piles, int n)
{  
  int a;
  cout << "Please input a, a can be any positive integer " << endl;
  cin >> a;

  double alpha, beta;
  
  alpha = (2-a+sqrt(a*a+4))/2;
  beta = alpha+a;

  vector<int> A;
  vector<int> B;
  A.push_back(0);
  B.push_back(0);

  //TODO change to C++ for_each
  for(int i=1;i<n;i++){
    A.push_back(floor(i*alpha));
    B.push_back(floor(i*beta));
  }
  
  init_game(piles,n);
  game(A,B,piles,a,n);
}

void recursive_characterizaton_of_P_Position(vector<int>& piles, int n)
{
  int a = 2;

  vector<int> A;
  vector<int> B;
  A.push_back(0);
  B.push_back(0);

  //TODO change to C++ for_each(begin,end,function_to_accumulate)
  for(int i=1;i<n;i++){
    get_min_positive(A, B);
    B.push_back(A.at(i)+a*i);
  }
  
  init_game(piles,n);
  game(A,B,piles,a,n);
}

void get_min_positive(vector<int>& A, const vector<int>& B)
{
  //merge A and B in sort order and find the missing pos number
  set<int> C;
  
  C.insert(A.begin(),A.end());
  C.insert(B.begin(),B.end());
  
  int mex = 0;
  for(auto c : C){
    if(c != mex){
      break;
    }
    mex++;
  }
  A.push_back(mex);
}

void init_game(vector<int>& piles, int n)
{  
  int piles_0,piles_1;
  srand(time(NULL));
  
  cout << "There is two piles of token : ";
  piles_1 = rand()%n;
  piles_0 = rand()%piles_1;
  piles.push_back(piles_0);
  piles.push_back(piles_1);

  cout << "(" << piles.at(0) << ", " << piles.at(1) << ")" << endl; 
  
}

void game(const vector<int>& A, const vector<int>& B, vector<int>& piles, int a, int n)
{ 
  bool winner = false;
  while(!winner){
    cout << "Player turn ... " << endl;
    cout << "How many piles do you want to remove?" << endl;
    int x, y;
    cin >> x;
    cin >> y;
    while(!isMoveAllow(piles,x,y,a)){
      cout << "Move " << x << ", " << y << " is invalid, please try again!" << endl;
      cin >> x;
      cin >> y;
    }
    
    piles.at(0) -= x;
    piles.at(1) -= y;

    cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
    
    if(piles.at(0) == 0 && piles.at(1) == 0){
      winner = true;
      cout << "Move " << x << ", " << y << " is wining move!" << endl;
      break;
    }

    cout << "Computer turn ... " << endl;
    //try to win first
    int computer_x = piles.at(0);
    int computer_y = piles.at(1);
    if(isMoveAllow(piles, computer_x, computer_y, a)){
      piles.at(0) -= computer_x;
      piles.at(1) -= computer_y;
      cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
      winner = true;
      break;;
    }

    recursive_and_algebraic_strategy(A,B,piles,a,n,winner); 
    cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
  }
}

void game_2(const map<int,vector<int>>& p_system, const map<int,vector<int>>& q_system, vector<int>& piles, int a, int n)
{
  bool winner = false;
  while(!winner){
    cout << "Player turn ... " << endl;
    cout << "How many piles do you want to remove?" << endl;
    int x, y;
    cin >> x;
    cin >> y;
    while(!isMoveAllow(piles,x,y,a)){
      cout << "Move " << x << ", " << y << " is invalid, please try again!" << endl;
      cin >> x;
      cin >> y;
    }
    
    piles.at(0) -= x;
    piles.at(1) -= y;

    cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
    
    if(piles.at(0) == 0 && piles.at(1) == 0){
      winner = true;
      cout << "Move " << x << ", " << y << " is wining move!" << endl;
      break;
    }

    cout << "Computer turn ... " << endl;
    int computer_x = piles.at(0);
    int computer_y = piles.at(1);
    if(isMoveAllow(piles, computer_x, computer_y, a)){
      piles.at(0) -= computer_x;
      piles.at(1) -= computer_y;
      cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
      winner = true;
      break;
    }
    arithmetic_strategy(p_system,q_system,piles,a,n,winner);
    cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
  }

}

void recursive_and_algebraic_strategy(const vector<int>& A, const vector<int>& B, vector<int>& piles, int a, int n, bool winner)
{
  int computer_x, computer_y;
  
  //Computer turn
  if(isCurrentStateP(A,B,piles)){
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
  else{
	  reach_P_position(A,B,piles,a);
  }
}

void arithmetic_strategy(const map<int,vector<int>>& p_system, const map<int,vector<int>>& q_system, vector<int>& piles, int a, int n, bool winner)
{
  int computer_x, computer_y;
  cout << "Arithmetic strategy " << endl;
  
  //FIXME possibly can throw the error if the key is not in map, consider to change to find
  vector<int> _Rp = p_system.at(piles.at(0));
  auto index_p = find_if(_Rp.rbegin(), _Rp.rend(), [] (int i) {
    return (i != 0);
  });

  int number_of_zeros_p = distance(_Rp.rbegin(), index_p);

  if(number_of_zeros_p%2 != 0) {
    piles.at(1) = piles.at(0);
    _Rp.pop_back();
    piles.at(0) = p_interpretation(p_system,_Rp);
  }
  else {
    _Rp.push_back(0);
    if(piles.at(1) > p_interpretation(p_system, _Rp)) {
      piles.at(1) = p_interpretation(p_system,_Rp);
    }
    else if(piles.at(1) == p_interpretation(p_system, _Rp)) {
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
      vector<int> _Rq = q_system.at(piles.at(m));
      auto index_q = find_if(_Rq.rbegin(), _Rq.rend(), [] (int i) {
        return (i != 0);
      });
      int number_of_zeros_q = distance(_Rq.rbegin(),index_q);
      if(number_of_zeros_q%2 != 0){
        piles.at(1) = p_interpretation(p_system, _Rq) + 1;
      }
      else {
        piles.at(1) = p_interpretation(p_system, _Rq);
      }
    }
  }

}
