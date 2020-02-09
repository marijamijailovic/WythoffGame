#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

void calculate_P_Position(vector<int>& A, vector<int>& B, int a, int n);
void get_min_positive(vector<int>& A, const vector<int>& B);

int main()
{
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

  cout << "Test" << endl;
  for(auto a : A){
    cout << a << " ";
  }
  cout << endl;
  

  for(auto b : B){
    cout << b << " ";
  }
  cout << endl;
  

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
