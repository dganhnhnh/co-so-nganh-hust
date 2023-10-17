#include <bits/stdc++.h> 
using namespace std;

int StepsToReachC(int a, int b, int c) {

    set<pair<int, int>> visited;
    queue<pair<int, int>> q;
    q.push({0, 0});
    visited.insert({0, 0});
    int steps = 0;

    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            if (x == c || y == c || x+y == c)
                return steps;

            // Fill the first jug
            if (x < a) {
                int newX = a;
                int newY = y;
                if (!visited.count({newX, newY})) {
                    q.push({newX, newY});
                    visited.insert({newX, newY});
                }
            }

            // Fill the second jug
            if (y < b) {
                int newX = x;
                int newY = b;
                if (!visited.count({newX, newY})) {
                    q.push({newX, newY});
                    visited.insert({newX, newY});
                }
            }

            // Pour from the first jug to the second jug
            if (x > 0) {
                int newX = max(0, x - (b - y));
                int newY = min(b, y + x);
                if (!visited.count({newX, newY})) {
                    q.push({newX, newY});
                    visited.insert({newX, newY});
                }
            }

            // Pour from the second jug to the first jug
            if (y > 0) {
                int newX = min(a, x + y);
                int newY = max(0, y - (a - x));
                if (!visited.count({newX, newY})) {
                    q.push({newX, newY});
                    visited.insert({newX, newY});
                }
            }

            // Empty the first jug
            if (x > 0) {
                int newX = 0;
                int newY = y;
                if (!visited.count({newX, newY})) {
                    q.push({newX, newY});
                    visited.insert({newX, newY});
                }
            }

            // Empty the second jug
            if (y > 0) {
                int newX = x;
                int newY = 0;
                if (!visited.count({newX, newY})) {
                    q.push({newX, newY});
                    visited.insert({newX, newY});
                }
            }
        }
        steps++;
    }

    return -1;
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    int result = StepsToReachC(a, b, c);
    cout << result << endl;
    return 0;
}