#include <bits/stdc++.h> 
using namespace std;

bool isCorrectExpression(const string& input) {
    stack<char> s;
    
    for (char c : input) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (s.empty()) {
                return false;
            }
            
            char top = s.top();
            s.pop();
            
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    
    return s.empty();
}

int main() {
    string input;
    cin >> input;
    
    if (isCorrectExpression(input)) {
        cout << "1" << endl;
    } else {
        cout << "0" << endl;
    }

    return 0;
}