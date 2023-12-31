#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <chrono>

using namespace std;

struct Order {
    string cID;
    string pID;
    int price;
    string sID;
    string timeStamp;
};

Order parseOrder(const string& line) {
    Order order;
    istringstream iss(line);
    iss >> order.cID >> order.pID >> order.price >> order.sID >> order.timeStamp;
    return order;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input_file.txt output_file.txt" << endl;
        return 1;
    }
    auto start_time = chrono::high_resolution_clock::now();

    vector<Order> orders;
    unordered_map<string, int> shopRevenue;
    map<pair<string, string>, int> customerShopRevenue;
    int totalRevenue = 0;

    ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line) && line != "#") {
        orders.emplace_back(parseOrder(line));
        shopRevenue[orders.back().sID] += orders.back().price;
        customerShopRevenue[{orders.back().cID, orders.back().sID}] += orders.back().price;
        totalRevenue += orders.back().price;
    }

    sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
        return a.timeStamp < b.timeStamp;
    });

    string outputFileName = "output.txt"; // Replace with your output file name
    ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    while (getline(inputFile, line) && line != "#") {
        if (line == "?total_number_orders") {
            outputFile << orders.size() << endl;
        } else if (line == "?total_revenue") {
            outputFile << totalRevenue << endl;
        } else if (line.compare(0, 17, "?revenue_of_shop ") == 0) {
            string sID = line.substr(17);
            outputFile << shopRevenue[sID] << endl;
        } else if (line.compare(0, 32, "?total_consume_of_customer_shop ") == 0) {
            string rest = line.substr(32);
            istringstream iss(rest);
            string cID, sID;
            iss >> cID >> sID;
            outputFile << customerShopRevenue[{cID, sID}] << endl;
        } else if (line.find("?total_revenue_in_period ") == 0) {
            string startTime, endTime;
            istringstream iss(line.substr(25));
            iss >> startTime >> endTime;

            int periodRevenue = 0;

            int startIdx = lower_bound(orders.begin(), orders.end(), startTime, [](const Order& a, const string& b) {
                return a.timeStamp < b;
            }) - orders.begin();

            int endIdx = upper_bound(orders.begin()+startIdx, orders.end(), endTime, [](const string& a, const Order& b) {
                return a < b.timeStamp;
            }) - orders.begin();

            if (endIdx >= orders.size()) {
                endIdx = orders.size();
            }

            for (int i = startIdx; i < endIdx; i++) {
                periodRevenue += orders[i].price;
            }

            outputFile << periodRevenue << endl;
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
