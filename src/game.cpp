#include "game.h"

Game::Game(int n) : _n(n)
{
  srand(static_cast<unsigned int>(time(NULL)));
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
