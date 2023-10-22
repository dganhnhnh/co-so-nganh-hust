//C++ 
#include <bits/stdc++.h> 
#include <map>
using namespace std;

vector <int> modConstList;
vector <int> modList;
int modCharList[26];

// use map to map char to mod m value 
std::map<char, int> modCharMap;

void calcModConst(int a, int m, int len) {
    int prevLen = modConstList.size();

    if (prevLen >= len) return;
    // if prev len = 1, start = 1, i from 1 to len-1
    int mod = 1;
    if (prevLen > 0) mod = modConstList[prevLen-1];
    else modConstList.push_back(mod);
    for (int i = prevLen; i < len; i++) {
        // because geometric progression, this method is effective 
        mod = (mod * a) % m;
        modConstList.push_back(mod);
    }
}

void calcModChar(int m){
    // for (int i=0; i<26; i++) {
    //     modCharList[i] = charToIntList[i] % m;
    // }
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

// void printVec(vector <int> v) {
//     for (int i=0; i<v.size(); i++) {
//         cout<<v[i]<<" ";
//     }
//     cout<<"\n";
// }

int main() 
{
    int n, m, a=256;
    cin>>n;
    cin >> m;
    calcModChar(m);
    for (char c = 'a'; c <= 'z'; ++c) {
        cout<< modCharMap[c]<<" ";
    }
    for (int i=0;i<n; i++){
        string s;
        cin>>s;
        // cout<<"s: "<<s<<"\n";
        int len = s.length();
        // cout<<"len: "<<len<<"\n";
        // calc all mods and save to modConstList
        calcModConst(a, m, len);
        // cout<< "modConstList: ";
        // printVec(modConstList);
        
        // calc all modChars and save to modList
        caclMod(s, m, len);
        // cout<< "modList: ";
        // printVec(modList);
        // take sum of all modList items and mod by m
        int sum = 0;
        for (int i=0; i<len; i++) {
            sum += modList[i];
        }
        int modSum = sum % m;
        cout << modSum << endl;
        
        modList.clear();
        // // modConstList.clear();
    }

    return 0;
}