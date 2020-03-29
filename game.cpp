#include "game.h"

Game::Game()
{
  srand(time(NULL));
  _piles1 = rand()%n;
  _piles0 = rand()%_piles1;
  _piles.push_back(_piles0);
  _piles.push_back(_piles1);
}

Game::~Game(){}

vector<int>& Game::get_piles()
{
  return _piles;
}

void Game::strategy()
{
  cout << "Game strategy " << endl;
  //p_positions();
  //recursive_and_algebraic_game();
}
// void Game::recursive_characterizaton_of_P_Position()
// {
//   int a = 2;
//
//   vector<int> A;
//   vector<int> B;
//   A.push_back(0);
//   B.push_back(0);
//
//   //TODO change to C++ for_each(begin,end,function_to_accumulate)
//   for(int i=1;i<n;i++){
//     Game::get_min_positive(A, B);
//     B.push_back(A.at(i)+a*i);
//   }
//
//   cout << "P Recursive Table " << endl;
//   cout << "A " << endl;
//   for_each(A.begin(),A.end(),[](int i){cout << i << " ";});
//   cout << endl;
//   cout << "B " << endl;
//   for_each(B.begin(),B.end(),[](int i){cout << i << " ";});
//   cout << endl;
//   //recursive_and_algebraic_game(A,B,piles,a,n);
// }

// void Game::get_min_positive(vector<int>& A, const vector<int>& B)
// {
//   //merge A and B in sort order and find the missing pos number
//   set<int> C;
//
//   C.insert(A.begin(),A.end());
//   C.insert(B.begin(),B.end());
//
//   int mex = 0;
//   for(auto c : C){
//     if(c != mex){
//       break;
//     }
//     mex++;
//   }
//   A.push_back(mex);
// }

// void Game::algebraic_characterization_of_P_Position()
// {
//   int a;
//   cout << "Please input a, a can be any positive integer " << endl;
//   cin >> a;
//
//   double alpha, beta;
//
//   alpha = (2-a+sqrt(a*a+4))/2;
//   beta = alpha+a;
//
//   vector<int> A;
//   vector<int> B;
//   A.push_back(0);
//   B.push_back(0);
//
//   //TODO change to C++ for_each
//   for(int i=1;i<n;i++){
//     A.push_back(floor(i*alpha));
//     B.push_back(floor(i*beta));
//   }
//
//   cout << "P Algebraic Table " << endl;
//   cout << "A " << endl;
//   for_each(A.begin(),A.end(),[](int i){cout << i << " ";});
//   cout << endl;
//   cout << "B " << endl;
//   for_each(B.begin(),B.end(),[](int i){cout << i << " ";});
//   cout << endl;
// }
//
// void Game::arithmetic_characterization_of_P_Position()
// {
//   int a;
//   cout << "Please input a, a can be any positive integer " << endl;
//   cin >> a;
//
//   //continued fractions and systems of numeration
//   //alpha is irrational 1<alpha<2
//
//   vector<int> alpha;
//   //alpha_continued_fractions(alpha, a, n);
//
//   vector<unsigned long long int> p;
//   vector<unsigned long long int> q;
//   //p_q_numerations(p, q, alpha, n);
//
//   map<int, vector<int>> p_system;
//   map<int, vector<int>> q_system;
//
//   //p_system_calculation(p_system, p, n);
//   //q_system_calculation(q_system, q, n);
//
//   //GAME PLAY
//
//   //R = (dm, dm-1, ... d0)
//   //R' = (dm, ..., d0, 0)
//   //R'' = (dm, ... , d1)
//
//   //FIRST CASE
//   //p-representation(Rp(i)) ends with even num of zeros --> An
//   //Bn = An+ an --> p-representation end with odd num of zeros
//
//   //Rp(Bn) = R'(An) //
//   //Ip(Rq(i)) = An ---> Rq(i) ends with even num of zeros
//   //Ip(Rq(i)) = An+1 ---> Rq(i) ends with odd num of zeros
//
//   //GAME
//   //curr position (x,y)
//   //1) calculate Rp(x)
//   //  --if it is end with odd num of zeros ---> x = Bk, end win move --> (x,y) = (Ip(Rp''(x)),x)
//   //  --if it is end with even num of zeros ---> x = Ak,
//   //      * y > Ip(Rp'(x)) ---> (x,y) = (x, Ip(Rp'(x)) win move
//   //      * y = Ip(Rp'(x)) ---> (x,y) is P , can't win from this pos
//   //      * y < Ip(Rp'(x)) ---> m = [(y-x)/a]
//
// }
