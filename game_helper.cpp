#include "game_helper.h"

Game_Helper::Game_Helper() {}

Game_Helper::~Game_Helper() {}

bool Game_Helper::isMoveAllow(vector<int>& piles, int a, int x, int y)
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

bool Game_Helper::zeros_piles(vector<int>& piles)
{
  return (piles.at(0) == 0 && piles.at(1) == 0);
}

void Game_Helper::player_move(vector<int>& piles, int a)
{
  cout << "How many piles do you want to remove?" << endl;
  int x, y;
  cin >> x;
  cin >> y;
  while(!isMoveAllow(piles,a,x,y)){
    cout << "Move " << x << ", " << y << " is invalid, please try again!" << endl;
    cin >> x;
    cin >> y;
  }

  piles.at(0) -= x;
  piles.at(1) -= y;

  cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
}

void Game_Helper::computer_move(vector<int>& piles, int a)
{
  if(!try_to_win(piles,a)) {
    int computer_x = rand()%piles.at(0);
    int computer_y = rand()%piles.at(1);

    while(!isMoveAllow(piles,a,computer_x,computer_y)){
      cout << "Move " << computer_x << ", " << computer_y << " is invalid, please try again!" << endl;
      computer_x = rand()%piles.at(0);
      computer_y = rand()%piles.at(1);
    }

    piles.at(0) -= computer_x;
    piles.at(1) -= computer_y;
  }
  cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
}

bool Game_Helper::try_to_win(vector<int>& piles, int a)
{
  //try to win first
  int computer_x = piles.at(0);
  int computer_y = piles.at(1);
  if(isMoveAllow(piles,a,computer_x,computer_y)){
    piles.at(0) -= computer_x;
    piles.at(1) -= computer_y;
    return true;
  }
  return false;
}
