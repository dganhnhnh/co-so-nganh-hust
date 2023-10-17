#include <bits/stdc++.h> 
using namespace std;

int main() {
    queue<int> myQueue;
    string line;

    while (getline(cin, line)) {
        if (line == "#") {
            break;
        }

        if (line.find("PUSH") == 0) {
            int value = stoi(line.substr(5));
            myQueue.push(value);
        } else if (line == "POP") {
            if (!myQueue.empty()) {
                cout << myQueue.front() << endl;
                myQueue.pop();
            } else {
                cout << "NULL" << endl;
            }
        }
    }

    return 0;
}