#include <bits/stdc++.h> 
using namespace std;

int main() {
    stack<int> myStack;
    string line;

    while (getline(cin, line)) {
        if (line == "#") {
            break;
        }

        if (line.find("PUSH") == 0) {
            int value = stoi(line.substr(5));
            myStack.push(value);
        } else if (line == "POP") {
            if (!myStack.empty()) {
                cout << myStack.top() << endl;
                myStack.pop();
            } else {
                cout << "NULL" << endl;
            }
        }
    }

    return 0;
}