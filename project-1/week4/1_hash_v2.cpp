//C++ 
#include <bits/stdc++.h> 
#include <map>
using namespace std;

vector <int> modConstList;
vector <int> modList;
int modCharList[26];

// use map to map char to mod m value 
std::map<char, int> modCharMap;

void calcModConst(int a, int m) {
    int mod = 1;
    modConstList.push_back(mod);
    for (int i = 0; i < 200; i++) {
        mod = (mod * a) % m;
        modConstList.push_back(mod);
    }
}

void calcModChar(int m){
    for (char c = 'a'; c <= 'z'; ++c) {
        modCharMap[c] = c % m;
    }
}

void caclMod(string s, int m, int len) {
    for (int i=0; i<len; i++) {
        // TODO get from modCharList and not recalculate 
        int modChar = (modCharMap[s[i]] * modConstList[len-i-1]) % m;
        modList.push_back(modChar);
    }
}

void printVec(vector <int> v) {
    for (int i=0; i<v.size(); i++) {
        cout<<v[i]<<" ";
    }
    cout<<"\n";
}

int main() 
{
    int n, m, a=256;
    cin>>n;
    cin >> m;
    calcModChar(m);
    calcModConst(a, m);
    for (int i=0;i<n; i++){
        string s;
        cin>>s;
        int len = s.length();
        caclMod(s, m, len);
        int sum = 0;
        for (int i=0; i<len; i++) {
            sum += modList[i];
        }
        int modSum = sum % m;
        cout << modSum << endl;
        
        modList.clear();
    }

    return 0;
}