#include <bits/stdc++.h> 
using namespace std;

int main() {
    int n;
    cin >> n;

    list<int> linkedList;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        linkedList.push_back(a);
    }

    string line;
    getline(cin, line); // Đọc dòng trống sau dòng n
    while (getline(cin, line)) {
        if (line == "#") {
            break;
        }
        
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "addlast") {
            int k;
            ss >> k;
            bool kExists = find(linkedList.begin(), linkedList.end(), k) != linkedList.end();
            if (!kExists) {
                linkedList.push_back(k);
            }
        } else if (command == "addfirst") {
            int k;
            ss >> k;
            bool kExists = find(linkedList.begin(), linkedList.end(), k) != linkedList.end();
            if (!kExists) {
                linkedList.push_front(k);
            }
        } else if (command == "addafter") {
            int u, v;
            ss >> u >> v;
            auto it = find(linkedList.begin(), linkedList.end(), v);
            bool uExists = find(linkedList.begin(), linkedList.end(), u) != linkedList.end();

            if (it != linkedList.end() && !uExists) {
                ++it;
                linkedList.insert(it, u);
            }
        } else if (command == "addbefore") {
            int u, v;
            ss >> u >> v;
            auto it = find(linkedList.begin(), linkedList.end(), v);
            bool uExists = find(linkedList.begin(), linkedList.end(), u) != linkedList.end();

            if (it != linkedList.end() && !uExists) {
                linkedList.insert(it, u);
            }
        } else if (command == "remove") {
            int k;
            ss >> k;
            linkedList.remove(k);
        } else if (command == "reverse") {
            linkedList.reverse();
        }
    }

    for (int key : linkedList) {
        cout << key << " ";
    }
    cout << endl;

    return 0;
}