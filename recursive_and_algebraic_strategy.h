#include "game.h"

void reach_P_position(const vector<int>& A,const vector<int>& B, vector<int>& piles, int a);
bool isCurrentStateP(const vector<int>& A, const vector<int>& B, const vector<int>& piles);
void recursive_and_algebraic_game(const vector<int>& A, const vector<int>& B, vector<int>& piles, int a, int n);
void recursive_and_algebraic_strategy(const vector<int>& A, const vector<int>& B, vector<int>& piles, int a, int n, bool winner);
