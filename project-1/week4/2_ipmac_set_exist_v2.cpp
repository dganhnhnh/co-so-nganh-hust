#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n,x; cin>>n;
    unordered_set<int> s;

    for (int i = 0; i < n; i++)
    {
        cin>>x;
        if(s.find(x) != s.end()){
            cout<<"1"<<endl;
        }
        else cout << "0" << endl;
        s.insert(x);
    }
    return 0;
}
