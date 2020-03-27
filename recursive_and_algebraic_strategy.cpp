#include "recursive_and_algebraic_strategy.h"

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

void recursive_and_algebraic_game(const vector<int>& A, const vector<int>& B, vector<int>& piles, int a, int n)
{
  bool winner = false;
  while(!winner){
    if(player_move(piles,a,winner)){
      break;
    }
    if(computer_move(piles,a,winner)){
      break;
    }
    recursive_and_algebraic_strategy(A,B,piles,a,n,winner);
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
