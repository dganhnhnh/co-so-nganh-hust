#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n,M,x,res=0; cin>>n>>M;
    unordered_set<int> s;

    for (int i = 0; i < n; i++)
    {
        cin>>x;
        s.insert(x);
    }
    auto it = s.begin();
    for (int i = 0; i < n; i++)
    {
        if (s.find(M - *it) != s.end() && s.find(M - *it) != it)
        {
            // cout << *it << " " << M - *it << endl;
            res++;
        }
        it++;
    }
    cout<<res/2;
    return 0;
}
