#include <iostream>

using namespace std;

void get_min_positive(vector<int> A, vector<int> B, int n)
{
 //merge A and B in sort order and find the missing pos number
 vector<int> C;
}

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
  
  A[0] = 0;
  A[1] = 1;
  B[0] = 0;

  for(int i=1;i<=n;i++){
   B.push_back(A[i]+a*n);
   get_min_positive(A, B, n);
  }

  return 0; 
}
