#include "game.h"

void alpha_continued_fractions(vector<int>& alpha, int a, int n);
void p_q_numerations(vector<unsigned long long int>& p, vector<unsigned long long int>& q, const vector<int>& alpha, int n);
void p_system_calculation(map<int, vector<int>>& p_system, const vector<unsigned long long int>& p, int n);
void q_system_calculation(map<int, vector<int>>& q_system, const vector<unsigned long long int>& q, int n);
int p_interpretation(const map<int,vector<int>>& p_system, vector<int>& R);
void arithmetic_game(const map<int,vector<int>>& p_system, const map<int,vector<int>>& q_system, vector<int>& piles, int a, int n);
void arithmetic_strategy(const map<int,vector<int>>& p_system, const map<int,vector<int>>& q_system, vector<int>& piles, int a, int n, bool winner);
