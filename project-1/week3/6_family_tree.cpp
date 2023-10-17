#include <bits/stdc++.h> 
using namespace std;

map<string, vector<string>> child_parent;
map<string, int> generation;

int countDescendants(const string &name) {
    int count = 0;
    if (child_parent.find(name) != child_parent.end()) {
        for (const string &child : child_parent[name]) {
            count += 1 + countDescendants(child);
        }
    }
    return count;
}

int countGenerations(const string &name) {
    if (generation.find(name) != generation.end()) {
        return generation[name];
    }

    if (child_parent.find(name) != child_parent.end()) {
        int maxGeneration = 0;
        for (const string &child : child_parent[name]) {
            maxGeneration = max(maxGeneration, countGenerations(child) + 1);
        }
        generation[name] = maxGeneration;
        return maxGeneration;
    } else {
        generation[name] = 0;
        return 0;
    }
}

int main() {
    string line;
     while (getline(cin, line) && line != "***") {
        string child, parent;
        istringstream iss(line);
        iss >> child >> parent;
        child_parent[parent].push_back(child);
    }

    while (getline(cin, line) && line != "***") {
        istringstream iss(line);
        string cmd, param;
        iss >> cmd >> param;
        if (cmd == "descendants") {
            int count = countDescendants(param);
            cout << count << endl;
        } else if (cmd == "generation") {
            int count = countGenerations(param);
            cout << count << endl;
        }
    }

    return 0;
}