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

// Function to process a transaction and update data structures
void processTransaction(const Transaction& transaction, unordered_map<string, int>& moneyFromAccount, set<string>& accountSet) {
    moneyFromAccount[transaction.fromAccount] += transaction.money;
    accountSet.insert(transaction.fromAccount);
    accountSet.insert(transaction.toAccount);
}

bool bfs(string startAccount, unordered_map<string, vector<string>> graph, int k) {
    queue<string> q;

    unordered_set<string> visited;

    q.push(startAccount);
    // visited.insert(startAccount);

    int currentLevel = 1;

    while (!q.empty() && currentLevel < k) {
        int levelSize = q.size();
        // cout << "levelSize "<< levelSize << endl;

        for (int i = 0; i < levelSize; ++i) {
            string currentAccount = q.front();
            // cout << "currentAccount "<< currentAccount << endl;
            // cout << "currentLevel "<< currentLevel << endl<<endl;
            q.pop();

            for (const string& neighbor : graph[currentAccount]) {
                // if (visited.find(neighbor) == visited.end()) {
                //     q.push(neighbor);
                //     visited.insert(neighbor);
                //     // cout << "pushed to queue "<< neighbor << endl;
                // }
                q.push(neighbor);
            }
        }

        // Move to the next level
        ++currentLevel;
    }

    // string currentAccount = q.front();
    // cout << "currentAccount "<< currentAccount << endl;
    // q.pop();
    int queue_size = q.size();
    // cout << "queue_size "<< queue_size << endl;
    if (currentLevel == k) {
        for (int i = 0; i < queue_size; ++i) {

            string currentAccount = q.front();
            // cout << "currentAccount "<< currentAccount << endl;
            q.pop();

            for (const string& neighbor : graph[currentAccount]) {
                // cout << "neighbor "<< neighbor << endl;
                if (neighbor == startAccount) {
                    return true;
                }
            }
        }
    }

    // return currentLevel > k+1;
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

int main() {
    vector<Transaction> transactions;
    unordered_map<string, int> moneyFromAccount;
    set<string> accountSet;
    unordered_map<string, vector<string>> graph;

    string line;
    while (getline(cin, line) && line != "#") {
        istringstream iss(line);
        Transaction transaction;
        iss >> transaction.fromAccount >> transaction.toAccount >> transaction.money >> transaction.timePoint >> transaction.atm;
        transactions.push_back(transaction);
        processTransaction(transaction, moneyFromAccount, accountSet);
        if (transaction.fromAccount != transaction.toAccount)
            graph[transaction.fromAccount].push_back(transaction.toAccount);
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
            cout << (bfs(account, graph, k) ? 1 : 0) << endl;
        }
    }

    return 0;
}
