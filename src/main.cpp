#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "game.h"
#include "recursive_and_algebraic.h"
#include "measure_time.cpp"

using namespace std;


int main()
{
  int game_option;
  int a;

  cout << "Do you want to measure the time of calculation the p-position by the strategies?(y/n)" << endl;
  char time;
  cin >> time;
  if(time == 'y'){
    MeasureTime::calculate_time();
  }

  cout << "##########   WYTHOFF GAME  ##########" << endl;
  cout << "There three way how we can calculate P-Position table (please choose the one of the option)" << endl;
  cout << "1) Recursive characterization of the P-Positions" << endl;
  cout << "2) Algebraic characterization of the P-Positions" << endl;
  cout << "3) Arithmetic characterization of the P-Positions" << endl;

  cin >> game_option;
  if(game_option == 1) {
    Recursive game(100, 2);
    game.strategy();
  }else if(game_option == 2) {
    cout << "Please input a, a can be any positive integer " << endl;
    cin >> a;
    Algebraic game(100, a);
    game.strategy();
  } else if(game_option == 3){
    cout << "Please input a, a can be any positive integer " << endl;
    cin >> a;
    Arithmetic game(100, a);
    game.strategy();
  }

  return 0;
}
