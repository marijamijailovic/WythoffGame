#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <time.h>

using namespace std;

void calculate_P_Position(vector<int>& A, vector<int>& B, int a, int n);
void get_min_positive(vector<int>& A, const vector<int>& B);
bool isMoveAllow(vector<int>& piles, int x, int y, int a);
bool isCurrentStateP(const vector<int>& A, const vector<int>& B, const vector<int>& piles);
vector<int> reach_P_position(const vector<int>& A,const vector<int>& B,const vector<int>& piles);

int main()
{
  
  //Recursive Characterization of the P-Positions
  //A_n = mex{A_i, B_i : i<n} -- mex najmanji nenegativan broj koji nije u A_n
  //mex{} = 0
  vector<int> A;
  vector<int> B;
  int n;
  int a = 2;

  cin >> n;
  
  A.push_back(0);
  B.push_back(0);

  calculate_P_Position(A,B,a,n);

/*  cout << "Test" << endl;
  for(auto a : A){
    cout << a << " ";
  }
  cout << endl;
  

  for(auto b : B){
    cout << b << " ";
  }
  cout << endl;
*/

  bool winner = false;
  vector<int> piles;
  srand(time(NULL));

  cout << "##########   WYTHOFF GAME  ##########" << endl;
  cout << "There is two piles of token : ";
  piles.push_back(rand()%100);
  piles.push_back(rand()%100);
  
  cout << "(" << piles.at(0) << ", " << piles.at(1) << ")" << endl; 
  
  //TODO
  while(!winner){
    //Player turn
    cout << "Player turn ... " << endl;
    cout << "How many piles do you want to remove?" << endl;
    int x, y, computer_x, computer_y;
    cin >> x;
    cin >> y;
    while(!isMoveAllow(piles,x,y,a)){
      cout << "Poruka upozorenja i pokusaj opet sa unosom" << endl;
      cin >> x;
      cin >> y;
    }
    
    piles.at(0) -= x;
    piles.at(1) -= y;

    cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
    
    if(piles.at(0) == 0 && piles.at(1) == 0){
      winner = true;
      cout << "Game over" << endl;
    }

    cout << "Computer turn ... " << endl;
    //Computer turn
    if(isCurrentStateP(A,B,piles)){
	//take random tokens, because it it P position, and whatever computer play the winner is player
	//but only if the player know the tactics
	computer_x = rand()%piles.at(0);
	computer_y = rand()%piles.at(1);
    }
    else{
	//piles(0) - computer_x = A
	//piles(1) - computer_y = B
	vector<int> computer_move = reach_P_position(A,B,piles);
    }
    //getPPositionTable();
    //if(CurrentStateIsP()) ---> computer is loser , but play anything
    //else{
    //  tryToReachToPPosition() ---> jer ako skoci na p poziciju, to je novo stanje i computer je pobedio
    //}

  }

  return 0; 
}

vector<int> reach_P_position(const vector<int>& A,const vector<int>& B,const vector<int>& piles, int a)
{
  vector<int> computer_move;
  //two case:
  //I  : if piles(0) is B_n, save n, then x = piles(0) and y = A_n,
  //II : if piles(0) is A_n, save n, if y > B_n then y  = B_n
  //                                 if y < B_n, d = y -x, m = donji_ceo(d/a) then x = A_m, y = B_m, m < n  
  //
  if(piles.
}

bool isCurrentStateP(const vector<int>& A, const vector<int>& B, const vector<int>& piles)
{
  if(A.find(piles.at(0)) && B.find(piles.at(1))) {
    return true;
  }
  return false;
}


bool isMoveAllow(vector<int>& piles, int x, int y, int a)
{
  if(x == 0 && y == 0){
    return false;
  } 

  if(x > 0 && y > 0 && !abs(x - y) < a){
    return false;
  }

  if((piles.at(0) - x) < 0 || (piles.at(1) - y) < 0){
    return false;
  }

  return true;
}

void calculate_P_Position(vector<int>& A, vector<int>& B, int a, int n)
{
  for(int i=1;i<=n;i++){
    get_min_positive(A, B);
    B.push_back(A.at(i)+a*i);
  }
}

void get_min_positive(vector<int>& A, const vector<int>& B)
{
  //merge A and B in sort order and find the missing pos number
  set<int> C;
  
  C.insert(A.begin(),A.end());
  C.insert(B.begin(),B.end());
  
  int mex = 0;
  for(auto c : C){
    if(c != mex){
      break;
    }
    mex++;
  }
  A.push_back(mex);
}
