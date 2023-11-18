#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>

using namespace std;

// Transaction structure with destination account, timestamp, and money
struct Transaction {
    string toAccount;
    string timestamp;
    int money;

    Transaction(string to, string time, int amount) : toAccount(to), timestamp(time), money(amount) {}
};

void processTransaction(const Transaction& transaction, unordered_map<string, int>& moneyFromAccount, set<string>& accountSet) {
    moneyFromAccount[transaction.toAccount] += transaction.money;
    accountSet.insert(transaction.toAccount);
    accountSet.insert(transaction.timestamp); // Assuming timestamp is also an account identifier
}

bool bfs(string startAccount, unordered_map<string, vector<Transaction>> graph, int k) {
    queue<pair<string, string>> q;  // Pair of (account, timestamp) for BFS
    unordered_set<string> visited;

    // Enqueue the start account and mark it as visited
    q.push({startAccount, "0"}); // Assuming "0" as the initial timestamp
    visited.insert(startAccount + "_0"); // Concatenate account and timestamp for uniqueness

    // BFS traversal
    int currentLevel = 1;

    while (!q.empty() && currentLevel < k) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; ++i) {
            pair<string, string> current = q.front();
            string currentAccount = current.first;
            string currentTimestamp = current.second;

            cout << "currentAccount " << currentAccount << " currentTimestamp " << currentTimestamp << " currentLevel " << currentLevel << endl << endl;

            q.pop();

            // Enqueue unvisited neighbors
            for (Transaction txn : graph[currentAccount]) {
                string neighbor = txn.toAccount;
                string neighborTimestamp = txn.timestamp;

                // Assuming timestamps are unique, concatenate them to differentiate nodes
                string neighborIdentifier = neighbor + "_" + neighborTimestamp;

                if (visited.find(neighborIdentifier) == visited.end()) {
                    q.push({neighbor, neighborTimestamp});
                    visited.insert(neighborIdentifier);
                }
            }
        }

        // Move to the next level
        ++currentLevel;
    }

    if (currentLevel == k) {
        // Process the last level (you can add your logic here)
        // for all accounts in the last level
        // check if they have a transaction with the start account
        // if yes, return true
        // else return false
        while (!q.empty()) {
            pair<string, string> current = q.front();
            string currentAccount = current.first;
            string currentTimestamp = current.second;

            cout << "currentAccount " << currentAccount << " currentTimestamp " << currentTimestamp << endl;

            q.pop();

            for (Transaction txn : graph[currentAccount]) {
                string neighbor = txn.toAccount;
                string neighborTimestamp = txn.timestamp;

                if (neighbor == startAccount && neighborTimestamp == currentTimestamp) {
                    return true;
                }
            }
        }
    }

    // Check if the BFS reached the required level
    return false;
}

int main() {
    // Example usage with Transaction object
    unordered_map<string, vector<Transaction>> graph;
    graph["A"] = {{"B", "2023-01-01", 10}, {"C", "2023-01-02", 20}};
    graph["B"] = {{"A", "2023-01-03", 15}, {"D", "2023-01-04", 25}};
    graph["C"] = {{"A", "2023-01-05", 30}, {"E", "2023-01-06", 35}};
    graph["D"] = {{"B", "2023-01-07", 40}};
    graph["E"] = {{"C", "2023-01-08", 45}};

    string startAccount = "A";
    int k = 4;

    bool cycleExists = bfs(startAccount, graph, k);

    if (cycleExists) {
        cout << "Cycle of length " << k << " exists." << endl;
    } else {
        cout << "Cycle of length " << k << " does not exist." << endl;
    }

    return 0;
}
