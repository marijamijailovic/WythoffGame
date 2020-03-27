#include "game.h"
#include "arithmetic_strategy.h"
#include "recursive_and_algebraic_strategy.h"

using namespace std;

void recursive_characterizaton_of_P_Position(vector<int>& piles, int n);
void algebraic_characterization_of_P_Position(vector<int>& piles, int n);
void arithmetic_characterization_of_P_Position(vector<int>& piles, int n);
void get_min_positive(vector<int>& A, const vector<int>& B);
void init_game(vector<int>& piles, int n);

int n = 100;
vector<int> piles;
int game_option;
