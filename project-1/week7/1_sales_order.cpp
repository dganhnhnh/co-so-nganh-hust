#include <bits/stdc++.h> 
#include <sstream>
#include <vector>
#include <map>

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
    // cout << "order.cID: " << order.cID << endl;
    // cout << "order.pID: " << order.pID << endl;
    // cout << "order.price: " << order.price << endl;
    // cout << "order.sID: " << order.sID << endl;
    // cout << "order.timeStamp: " << order.timeStamp << endl;
    return order;
}

int main() {
    vector<Order> orders;
    map<string, int> shopRevenue;
    map<pair<string, string>, int> customerShopRevenue;
    int totalRevenue = 0;

    string line;
    while (getline(cin, line) && line != "#") {
        Order order = parseOrder(line);
        orders.push_back(order);
        shopRevenue[order.sID] += order.price;
        customerShopRevenue[{order.cID, order.sID}] += order.price;
        // cout<< "customerShopRevenue[{order.cID, order.sID}]: "<<customerShopRevenue[{order.cID, order.sID}]<<endl;
        totalRevenue += order.price;
    }

    while (getline(cin, line) && line != "#") {
        if (line == "?total_number_orders") {
            cout << orders.size() << endl;
        } else if (line == "?total_revenue") {
            cout << totalRevenue << endl;
        } else if (line.find("?revenue_of_shop ") == 0) {
            string sID = line.substr(17);
            cout << sID << endl;
            cout << shopRevenue[sID] << endl;
        } else if (line.find("?total_consume_of_customer_shop ") == 0) {
            string rest = line.substr(32);
            istringstream iss(rest);
            string cID, sID;
            iss >> cID >> sID;
            cout << cID << " " << sID << endl;
            cout << customerShopRevenue[{cID, sID}] << endl;
        } else if (line.find("?total_revenue_in_period ") == 0) {
            string startTime, endTime;
            istringstream iss(line.substr(26));
            iss >> startTime >> endTime;

            int periodRevenue = 0;
            for (const auto& order : orders) {
                if (order.timeStamp >= startTime && order.timeStamp <= endTime) {
                    periodRevenue += order.price;
                }
            }

            cout << periodRevenue << endl;
        }
    }

    return 0;
}
