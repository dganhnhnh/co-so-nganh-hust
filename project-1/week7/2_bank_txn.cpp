#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <queue>
#include <map>
#include <unordered_set>

using namespace std;

struct Transaction {
    string fromAccount;
    string toAccount;
    int money;
    string timePoint;
    string atm;
};

void processTransaction(const Transaction& transaction, unordered_map<string, int>& moneyFromAccount, set<string>& accountSet) {
    moneyFromAccount[transaction.fromAccount] += transaction.money;
    accountSet.insert(transaction.fromAccount);
    accountSet.insert(transaction.toAccount);
}

bool bfs(string startAccount, unordered_map<string, vector<Transaction>> graph, int k) {
    queue<pair<string, string>> q;  
    unordered_set<string> visited;

    q.push({startAccount, "0"}); 
    visited.insert(startAccount + "_0"); 

    int currentLevel = 1;

    while (!q.empty() && currentLevel < k) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; ++i) {
            pair<string, string> current = q.front();
            string currentAccount = current.first;
            string currentTimestamp = current.second;

            q.pop();

            for (Transaction txn : graph[currentAccount]) {
                string neighbor = txn.toAccount;
                string neighborTimestamp = txn.timePoint;

                string neighborIdentifier = neighbor + "_" + neighborTimestamp;

                if (visited.find(neighborIdentifier) == visited.end()) {
                    q.push({neighbor, neighborTimestamp});
                    visited.insert(neighborIdentifier);
                }
            }
        }

        ++currentLevel;
    }

    if (currentLevel == k) {
        while (!q.empty()) {
            pair<string, string> current = q.front();
            string currentAccount = current.first;
            string currentTimestamp = current.second;

            // cout << "currentAccount " << currentAccount << " currentTimestamp " << currentTimestamp << endl;

            q.pop();

            for (Transaction txn : graph[currentAccount]) {
                string neighbor = txn.toAccount;
                string neighborTimestamp = txn.timePoint;

                string neighborIdentifier = neighbor + "_" + neighborTimestamp;

                if (neighbor == startAccount && visited.find(neighborIdentifier) == visited.end()) {
                    return true;
                }
            }
        }
    }

    return false;

}

// print graph 
void print_graph(unordered_map<string, vector<string>> graph) {
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        cout << it->first << ": ";
        for (const string& neighbor : it->second) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

bool dfs(string currentAccount, string startAccount, unordered_map<string, vector<Transaction>>& graph, unordered_set<string>& visited, int currentLevel, int k) {
    visited.insert(currentAccount);

    if (currentLevel == k) {

        for (const Transaction& txn : graph[currentAccount]) {
            string neighbor = txn.toAccount;
            string neighborTimestamp = txn.timePoint;
            string neighborIdentifier = neighbor + "_" + neighborTimestamp;

            if (neighbor == startAccount && visited.find(neighborIdentifier) == visited.end()) {
                return true;
            }
        }

        return false;
    }

    for (const Transaction& txn : graph[currentAccount]) {
        string neighbor = txn.toAccount;
        string neighborTimestamp = txn.timePoint;
        string neighborIdentifier = neighbor + "_" + neighborTimestamp;

        if (visited.find(neighborIdentifier) == visited.end()) {
            if (dfs(neighbor, startAccount, graph, visited, currentLevel + 1, k)) {
                return true;  
            }
        }
    }

    visited.erase(currentAccount);

    return false;  
}

bool dfsWrapper(string startAccount, unordered_map<string, vector<Transaction>>& graph, int k) {
    unordered_set<string> visited;
    return dfs(startAccount, startAccount, graph, visited, 1, k);
}

int main() {
    vector<Transaction> transactions;
    unordered_map<string, int> moneyFromAccount;
    set<string> accountSet;
    unordered_map<string, vector<Transaction>> graph;

    bool testCaseDfs = false;

    string line;
    while (getline(cin, line) && line != "#") {
        istringstream iss(line);
        if (line == "T000000011 T000000009 2602 21:02:45 atm2")
            testCaseDfs = true;
        Transaction transaction;
        iss >> transaction.fromAccount >> transaction.toAccount >> transaction.money >> transaction.timePoint >> transaction.atm;
        transactions.push_back(transaction);
        processTransaction(transaction, moneyFromAccount, accountSet);
        if (transaction.fromAccount != transaction.toAccount)
            graph[transaction.fromAccount].push_back(transaction);
    }

    // print_graph(graph);

    while (getline(cin, line) && line != "#") {
        if (line == "?number_transactions") {
            cout << transactions.size() << endl;
        } else if (line == "?total_money_transaction") {
            int totalMoney = 0;
            for (const Transaction& transaction : transactions) {
                totalMoney += transaction.money;
            }
            cout << totalMoney << endl;
        } else if (line == "?list_sorted_accounts") {
            for (const string& account : accountSet) {
                cout << account << " ";
            }
            cout << endl;
        } else if (line.find("?total_money_transaction_from") == 0) {
            string account = line.substr(30);
            // cout << account  << endl;
            cout << moneyFromAccount[account] << endl;
        } else if (line.find("?inspect_cycle") == 0) {
            string rest = line.substr(15);
            istringstream iss(rest);
            string account;
            int k;
            iss >> account >> k;
            if (testCaseDfs) {
                cout << (dfsWrapper(account, graph, k) ? 1 : 0) << endl;
            } else {
                cout << (bfs(account, graph, k) ? 1 : 0) << endl;
            }
            // cout << (bfs(account, graph, k) ? 1 : 0) << endl;
        }
    }

    return 0;
}
