#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <time.h>

using namespace std;

void calculate_P_Position(vector<int>& A, vector<int>& B, int a, int n);
void get_min_positive(vector<int>& A, const vector<int>& B);

int main()
{
  //TODO allowedMove()
  
  //Recursive Characterization of the P-Positions
  //A_n = mex{A_i, B_i : i<n} -- mex najmanji nenegativan broj koji nije u A_n
  //mex{} = 0
  //
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
  int x, y;
  srand(time(NULL));

  cout << "##########   WYTHOFF GAME  ##########" << endl;
  cout << "There is two piles of token : ";
  x = rand()%100;
  y = rand()%100;
  
  cout << "(" << x << ", " << y << ")" << endl; 
  
  //TODO
 /* while(!winner){
    //Player turn
    cout << "How many piles do you want to remove?" << endl;
    cin >> x;
    cin >> y;
    while(!isMoveAllow(x,y)){
      cout << "Poruka upozorenja i pokusaj opet sa unosom" << endl;
      cin >> x;
      cin >> y;
    }
    
    cout << "Current state od piles is (<< x << ", " << y << ")" << endl;

    //Computer turn
    //getPPositionTable();
    //if(CurrentStateIsP()) ---> computer is loser , but play anything
    //else{
      tryToReachToPPosition() ---> jer ako skoci na p poziciju, to je novo stanje i computer je pobedio
    }

  }*/

  return 0; 
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
