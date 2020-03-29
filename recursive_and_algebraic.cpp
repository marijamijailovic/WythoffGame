#include "recursive_and_algebraic.h"
#include "game_helper.h"

Recursive_and_Algebraic::Recursive_and_Algebraic(int a) : _a(a) {}

Recursive_and_Algebraic::~Recursive_and_Algebraic() {}

void Recursive_and_Algebraic::strategy()
{
  cout << "Recursive and Algebaric strategy " << endl;
  p_positions();
  recursive_and_algebraic_game(get_piles());
}

void Recursive_and_Algebraic::p_positions()
{
  cout << "RA positions " << endl;
}

void Recursive_and_Algebraic::recursive_and_algebraic_game(vector<int>& piles)
{
  cout << "There is two piles of token : ";
  cout << "(" << piles.at(0) << ", " << piles.at(1) << ")" << endl;
  bool winner = false;
  while(!winner){
    if(Game_Helper::player_move(piles,_a,winner)){
      break;
    }
    if(Game_Helper::computer_move(piles,_a,winner)){
      break;
    }
    recursive_and_algebraic_strategy(piles,winner);
    cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
  }
}

void Recursive_and_Algebraic::recursive_and_algebraic_strategy(vector<int>& piles, bool winner)
{
  cout << "TEST " << piles.at(0) << " " << piles.at(1) << endl;
  int computer_x, computer_y;

  //Computer turn
  if(isCurrentStateP(piles)){
    cout << "P pozicija " << endl;
    computer_x = rand()%piles.at(0);
	  computer_y = rand()%piles.at(1);

    while(!Game_Helper::isMoveAllow(piles,_a,computer_x,computer_y)){
      computer_x = rand()%piles.at(0);
      computer_y = rand()%piles.at(1);
    }

    piles.at(0) -= computer_x;
    piles.at(1) -= computer_y;
  }
  else{
	  reach_P_position(piles);
  }
}

bool Recursive_and_Algebraic::isCurrentStateP(vector<int>& piles)
{
  auto it_A = find(_A.begin(), _A.end(), piles.at(0));
  auto it_B = find(_B.begin(), _B.end(), piles.at(1));

  if(find(_A.begin(), _A.end(), piles.at(0)) != _A.end() && find(_B.begin(), _B.end(), piles.at(1)) != _B.end() && distance(_A.begin(), it_A) == distance(_B.begin(), it_B)) {
    return true;
  }
  return false;
}

void Recursive_and_Algebraic::reach_P_position(vector<int>& piles)
{
  cout << "Trazi P poziciju " << piles.at(0) << " " << piles.at(1) << endl;
  //two case:
  //I  : if piles(0) is B_n, save n, then x = piles(0) and y = A_n,
  //II : if piles(0) is A_n, save n, if y > B_n then y  = B_n
  //                                 if y < B_n, d = y -x, m = donji_ceo(d/a) then x = A_m, y = B_m, m < n
  if(find(_B.begin(), _B.end(), piles.at(0)) != end(_B)){
    cout << "Prvi slucaj x je u B " << endl;
    //(47, 74)
    //piles_0 = 47, piles_1 = 74
    //piles_1 = piles_0
    //piles_0 = ono sto je na A poziciji koja odgovara onoj gde je B 47
    //(19, 47)
    auto it = find(_B.begin(),_B.end(), piles.at(0));
    int index = distance(_B.begin(), it);
    piles.at(1) = piles.at(0);
    piles.at(0) = _A.at(index);
  }else if(find(_A.begin(), _A.end(), piles.at(0)) != end(_A)){
    auto it = find(_A.begin(),_A.end(), piles.at(0));
    int index = distance(_A.begin(), it);
    if(piles.at(1) >= _B.at(index)){
      cout << "Prvi slucaj y je > B " << endl;
      //(19,74)
      //piles_0 = 19, piles_1 = 74
      //piles_0 = piles_0
      //piles_1 = ono sto je na B poziciji koja odgovvara onoj gde je A 19
      //computer_move.push_back(piles.at(0));
      //computer_move(_B.at(find(index)));
      piles.at(1) = _B.at(index);
    }
    else{
      int d = abs(piles.at(1) - piles.at(0));
      int m = floor(d/_a);
      piles.at(0) = _A.at(m);
      piles.at(1) = _B.at(m);
    }
  }
}



