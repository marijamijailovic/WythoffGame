#include <iostream>
#include <algorithm>
#include <vector>
#include "game.h"
#include "recursive_and_algebraic.h"
#include "arithmetic.h"
#include "recursive.h"
#include "algebraic.h"
#include "measure_time.cpp"

using namespace std;


int main()
{
  int game_option;
  int a;

  cout << "Do you want to measure the time of calculation the p-position by the strategies?(y/n)" << endl;
  char timeOption;
  cin >> timeOption;
  if(timeOption == 'y'){
    Recursive recursive(2);
    Algebraic algebraic(2);
    Arithmetic arithmetic(2);
    auto rec = bind(&Recursive::p_positions,recursive);
    cout << "Recoursive " << MeasureTime::calculate_time(rec) << endl;
    auto alg = bind(&Algebraic::p_positions,algebraic);
    cout << "Algebraic " << MeasureTime::calculate_time(alg) << endl;
    auto art = bind(&Arithmetic::arithmetic_characterization_of_P_Position,arithmetic);
    cout << "Arithmetic " << MeasureTime::calculate_time(art) << endl;
  }

  cout << "##########   WYTHOFF GAME  ##########" << endl;
  cout << "There three way how we can calculate P-Position table (please choose the one of the option)" << endl;
  cout << "1) Recursive characterization of the P-Positions" << endl;
  cout << "2) Algebraic characterization of the P-Positions" << endl;
  cout << "3) Arithmetic characterization of the P-Positions" << endl;

  cin >> game_option;
  if(game_option == 1) {
    Recursive game(2);
    game.strategy();
  }else if(game_option == 2) {
    cout << "Please input a, a can be any positive integer " << endl;
    cin >> a;
    Algebraic game(a);
    game.strategy();
  } else if(game_option == 3){
    cout << "Please input a, a can be any positive integer " << endl;
    cin >> a;
    Arithmetic game(a);
    game.strategy();
  }

  return 0;
}
