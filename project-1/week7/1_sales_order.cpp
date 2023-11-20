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
    string timePoint;
};

int ord(char c)
{
    return c-'0' ;
}

int convertTimetoInt(string c)
{
    return (ord(c[0])*10+ord(c[1]))*60*60
          +(ord(c[3])*10+ord(c[4]))*60+(ord(c[6])*10+ord(c[7])) ;
}

Order parseOrder(const string& line) {
    Order order;
    istringstream iss(line);
    iss >> order.cID >> order.pID >> order.price >> order.sID >> order.timePoint;
    return order;
}

int main() {
    vector<Order> orders;
    unordered_map<string, int> shopRevenue;
    map<pair<string, string>, int> customerShopRevenue;
    int totalRevenue = 0;
    long long s[24*60*60];

    string line;
    while (getline(cin, line) && line != "#") {
        Order order = parseOrder(line);
        orders.push_back(order);
        shopRevenue[order.sID] += order.price;
        customerShopRevenue[{order.cID, order.sID}] += order.price;
        totalRevenue += order.price;
        s[convertTimetoInt(order.timePoint)]+= order.price;
    }

    for(int i=1;i<24*60*60;++i)
        s[i]+=s[i-1];

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

            cout<<s[convertTimetoInt(endTime)]-(convertTimetoInt(startTime)==0?0:s[convertTimetoInt(startTime)-1]) ;
        }
    }

    return 0;
}
