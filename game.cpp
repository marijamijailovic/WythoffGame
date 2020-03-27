#include "game.h"

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

bool player_move(vector<int>& piles, int a, bool winner)
{
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
  }
  return winner;
}

bool computer_move(vector<int>& piles, int a, bool winner)
{
  cout << "Computer turn ... " << endl;
  //try to win first
  int computer_x = piles.at(0);
  int computer_y = piles.at(1);
  if(isMoveAllow(piles, computer_x, computer_y, a)){
    piles.at(0) -= computer_x;
    piles.at(1) -= computer_y;
    cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
    winner = true;
  }
  return winner;
}
