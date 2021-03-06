#include "recursive_and_algebraic.h"
#include "game_helper.h"

Recursive_and_Algebraic::Recursive_and_Algebraic(int n, int a)
    : Game(n), _a(a) {}

Recursive_and_Algebraic::~Recursive_and_Algebraic() {}

void Recursive_and_Algebraic::strategy() {
  p_positions();
  recursive_and_algebraic_game(get_piles());
}

void Recursive_and_Algebraic::recursive_and_algebraic_game(vector<int> &piles) {
  cout << "There is two piles of token : ";
  cout << "(" << piles[0] << ", " << piles[1] << ")" << endl;
  while (!Game_Helper::zeros_piles(piles)) {
    cout << "Player turn ... " << endl;
    Game_Helper::player_move(piles, _a);
    if (Game_Helper::zeros_piles(piles)) {
      break;
    }
    cout << "Computer turn ... " << endl;
    reach_P_position(piles);
    cout << "Current state od piles is (" << piles[0] << ", " << piles[1] << ")"
         << endl;
  }
}

void Recursive_and_Algebraic::reach_P_position(vector<int> &piles) {
  // two case:
  // I  : if piles(0) is B_n, save n, then x = piles(0) and y = A_n,
  // II : if piles(0) is A_n, save n, if y > B_n then y  = B_n
  //                                 if y < B_n, d = y -x, m = floor(d/a) then x
  //                                 = A_m, y = B_m, m < n
  if (find(_B.begin(), _B.end(), piles[0]) != end(_B)) {
    auto it = find(_B.begin(), _B.end(), piles[0]);
    vector<int>::size_type index =
        static_cast<vector<int>::size_type>(distance(_B.begin(), it));
    piles[1] = piles[0];
    piles[0] = _A[index];
  } else if (find(_A.begin(), _A.end(), piles[0]) != end(_A)) {
    auto it = find(_A.begin(), _A.end(), piles[0]);
    vector<int>::size_type index =
        static_cast<vector<int>::size_type>(distance(_A.begin(), it));
    if (piles[1] > _B[index]) {
      piles[1] = _B[index];
    } else if (piles[1] < _B[index]) {
      int d = abs(piles[1] - piles[0]);
      vector<int>::size_type m = static_cast<vector<int>::size_type>(d / _a);
      piles[0] = _A[m];
      piles[1] = _B[m];
    } else {
      Game_Helper::computer_move(piles, _a);
    }
  }
}
