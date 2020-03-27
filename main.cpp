#include "main.h"

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
  recursive_and_algebraic_game(A,B,piles,a,n);
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
  recursive_and_algebraic_game(A,B,piles,a,n);
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
  arithmetic_game(p_system,q_system,piles,a,n);
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
