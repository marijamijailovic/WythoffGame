#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <set>
#include <time.h>
#include <cmath>

using namespace std;

void calculate_P_Position(vector<int>& A, vector<int>& B, int a, int n);
void get_min_positive(vector<int>& A, const vector<int>& B);
bool isMoveAllow(vector<int>& piles, int x, int y, int a);
bool isCurrentStateP(const vector<int>& A, const vector<int>& B, const vector<int>& piles);
void reach_P_position(const vector<int>& A, const vector<int>& B, vector<int>& piles, int a);

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
      cout << "Move " << x << ", " << y << " is invalid, please try again!" << endl;
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
      cout << "P Pozicija" << endl;
      //TODO ne RAND, vec pokusaj da skines sto vise mozes 
      //AKO JE (0,y) ili (x,0) onda uzmi sve X, ili Y --> FIRST TYPE OF MOVE
      //AKO JE (x,y) onda pokusaj da skines sve tako da je rezultat (0,0)
      computer_x = rand()%piles.at(0);
	    computer_y = rand()%piles.at(1);
   
      while(!isMoveAllow(piles,computer_x,computer_y,a)){
        cout << "Move " << computer_x << ", " << computer_y << " is invalid, please try again!" << endl;
        computer_x = rand()%piles.at(0);
	      computer_y = rand()%piles.at(1);
      }
    
      piles.at(0) -= computer_x;
      piles.at(1) -= computer_y;
    }
    else{
      cout << "Nije P pozicija " << endl;
	    reach_P_position(A,B,piles,a);
    }
    
    cout << "Current state od piles is ("<< piles.at(0) << ", " << piles.at(1) << ")" << endl;
  }

  return 0; 
}

void reach_P_position(const vector<int>& A,const vector<int>& B, vector<int>& piles, int a)
{
  cout << "Pokusaj da dosegnes do P pozicije ... " << endl;
  //two case:
  //I  : if piles(0) is B_n, save n, then x = piles(0) and y = A_n,
  //II : if piles(0) is A_n, save n, if y > B_n then y  = B_n
  //                                 if y < B_n, d = y -x, m = donji_ceo(d/a) then x = A_m, y = B_m, m < n  
  /*if(find(B.begin(),B.end(), piles.at(0)) != end(B)){ 
    cout << "Prvi slucaj x je u B " << endl;
    auto it = find(B.begin(),B.end(), piles.at(0));
    int index = distance(B.begin(), it);
    cout << index << endl; 
  }*/
  if(find(B.begin(), B.end(), piles.at(0)) != end(B)){
    //computer_move.push_back(piles.at(0));
    cout << "Prvi slucaj x je u B " << endl;
    //(47, 74)
    //piles_0 = 47, piles_1 = 74
    //piles_1 = piles_0
    //piles_0 = ono sto je na A poziciji koja odgovara onoj gde je B 47
    //(19, 47)
    auto it = find(B.begin(),B.end(), piles.at(0));
    int index = distance(B.begin(), it);
    cout << "Na poziciji " << index << " je " << A.at(index) << endl;
    piles.insert(piles.end(), piles.at(0));
    piles.insert(piles.begin(), A.at(index));
  }
  else if(find(A.begin(), A.end(), piles.at(0)) != end(A)){
    cout << "Drugi slucaj x je u A " << endl;
    auto it = find(A.begin(),A.end(), piles.at(0));
    int index = distance(A.begin(), it);
    if(piles.at(1) >= B.at(index)){
      cout << "Prvi slucaj y je > B " << endl;
      //(19,74)
      //piles_0 = 19, piles_1 = 74
      //piles_0 = piles_0
      //piles_1 = ono sto je na B poziciji koja odgovvara onoj gde je A 19
      //computer_move.push_back(piles.at(0));
      //computer_move(B.at(find(index)));
      cout << "Na poziciji " << index << " je " << B.at(index) << endl;
      piles.insert(piles.end(), B.at(index));
    }
    else{
      cout << "Drugi slucaj y je < B " << endl;
      int d = piles.at(1) - piles.at(0);
      int m = floor(d/a);
      piles.insert(piles.begin(),A.at(m));
      piles.insert(piles.end(),B.at(m));
    }
  }

}

bool isCurrentStateP(const vector<int>& A, const vector<int>& B, const vector<int>& piles)
{
  if(find(A.begin(), A.end(), piles.at(0)) != end(A) && find(B.begin(), A.begin(), piles.at(1)) != end(B)) {
    return true;
  }
  return false;
}


bool isMoveAllow(vector<int>& piles, int x, int y, int a)
{
  if(x == 0 && y == 0){
    return false;
  } 

  if(x > 0 && y > 0 && !(abs(x - y) < a)){
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
