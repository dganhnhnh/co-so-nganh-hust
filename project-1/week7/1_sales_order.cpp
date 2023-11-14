#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <tuple>

using namespace std;

using Order = tuple<string, string, int, string, string>;

Order parseOrder(const string& line) {
    Order order;
    istringstream iss(line);
    iss >> get<0>(order) >> get<1>(order) >> get<2>(order) >> get<3>(order) >> get<4>(order);
    return order;
}

int main() {
    vector<Order> orders;
    unordered_map<string, int> shopRevenue;
    map<pair<string, string>, int> customerShopRevenue;
    int totalRevenue = 0;

    string line;
    while (getline(cin, line) && line != "#") {
        Order order = parseOrder(line);
        orders.push_back(order);
        shopRevenue[get<3>(order)] += get<2>(order);
        customerShopRevenue[{get<0>(order), get<3>(order)}] += get<2>(order);
        totalRevenue += get<2>(order);
    }

    sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
        return get<4>(a) < get<4>(b);
    });

    while (getline(cin, line) && line != "#") {
        if (line == "?total_number_orders") {
            cout << orders.size() << endl;
        } else if (line == "?total_revenue") {
            cout << totalRevenue << endl;
        } else if (line.compare(0, 17, "?revenue_of_shop ") == 0) {
            string sID = line.substr(17);
            cout << shopRevenue[sID] << endl;
        } else if (line.compare(0, 32, "?total_consume_of_customer_shop ") == 0) {
            string rest = line.substr(32);
            istringstream iss(rest);
            string cID, sID;
            iss >> cID >> sID;
            cout << customerShopRevenue[{cID, sID}] << endl;
        } else if (line.find("?total_revenue_in_period ") == 0) {
            string startTime, endTime;
            istringstream iss(line.substr(25));
            iss >> startTime >> endTime;

            int periodRevenue = 0;

            int startIdx = lower_bound(orders.begin(), orders.end(), startTime, [](const Order& a, const string& b) {
                return get<4>(a) < b;
            }) - orders.begin();

            int endIdx = upper_bound(orders.begin(), orders.end(), endTime, [](const string& a, const Order& b) {
                return a < get<4>(b);
            }) - orders.begin();

            if (endIdx >= orders.size()) {
                endIdx = orders.size();
            }

            for (int i = startIdx; i < endIdx; i++) {
                periodRevenue += get<2>(orders[i]);
            }

            cout << periodRevenue << endl;
        }
    }

    return 0;
}
