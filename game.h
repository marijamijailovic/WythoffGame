#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>
#include <set>
#include <time.h>
#include <cmath>

using namespace std;

bool isMoveAllow(vector<int>& piles, int x, int y, int a);
bool player_move(vector<int>& piles, int a, bool winner);
bool computer_move(vector<int>& piles, int a, bool winner);
