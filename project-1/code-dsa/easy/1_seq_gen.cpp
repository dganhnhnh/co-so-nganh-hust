//C++ 
#include <bits/stdc++.h> 
using namespace std;

void print_sol(int x[], int n){
   for (int i=0; i<n; i++){
      cout << x[i];
   }
   cout << endl;
}

void TRY(int k, int x[], int n){
   for (int i=0; i<= 1; i++){
      int tmp = i;
      if (x[k] == -1){
         x[k]= tmp;
         if (k==n-1) print_sol(x, n);
         else TRY(k+1, x,n);
         x[k] = -1;
      }
   }
}

int main() 
{ 
   int n; cin>>n;
   int x[n];
   for (int i = 0; i < n; i++) {
        x[i] = -1;
   }
   TRY(0, x,n);
   return 0;
}
