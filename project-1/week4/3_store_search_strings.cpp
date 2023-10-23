#include <bits/stdc++.h> 
#include <unordered_set>
#include <string>
using namespace std;

int main() {
    unordered_set<string> db;
    string key;

    while (true) {
        cin >> key;
        if (key == "*") {
            break;
        }
        db.insert(key);
    }

    while (true) {
        string cmd, k;
        cin >> cmd >> k;
        if (cmd == "***") {
            break;
        }

        if (cmd == "find") {
            if (db.find(k) != db.end()) {
                cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
        } else if (cmd == "insert") {
            if (db.insert(k).second) {
                cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
        }
    }

    return 0;
}
