#include <bits/stdc++.h>
using namespace std;

const int MAXINT = (int)1e5+5;

int ord(char c)
{
    return c - '0';
}

int timeStrToInt(string c)
{
    return (ord(c[0]) * 10 + ord(c[1])) * 60 * 60 + (ord(c[3]) * 10 + ord(c[4])) * 60 + (ord(c[6]) * 10 + ord(c[7]));
}

int main()
{
    unordered_map<string, int> customer;
    unordered_map<string, int> totalRev[MAXINT];
    unordered_map<string, int> revenueOfShop;
    long long s[24 * 60 * 60];

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long totalRevenue = 0;
    int numOrder = 0;
    int numCustomer = 0;
    string line;
    while (getline(cin, line) && line != "#") {
        string customerID, productID, shopID, timePoint;
        int price;
        istringstream iss(line);
        iss >> customerID >> productID >> price >> shopID >> timePoint;
        s[timeStrToInt(timePoint)] += price;
        totalRevenue += 1LL * price;
        numOrder++;
        if (customer[customerID] == 0) customer[customerID] = ++numCustomer;
        totalRev[customer[customerID]][shopID] += price;
        revenueOfShop[shopID] += price;
    }
    for (int i = 1; i < 24 * 60 * 60; ++i)
        s[i] += s[i - 1];

    while (getline(cin, line) && line != "#") {
        if (line == "?total_number_orders") {
            cout << numOrder;
        } else if (line == "?total_revenue") {
            cout << totalRevenue;
        } else if (line.compare(0, 17, "?revenue_of_shop ") == 0) {
            string sID = line.substr(17);
            cout << revenueOfShop[sID] << endl;
        } else if (line.compare(0, 32, "?total_consume_of_customer_shop ") == 0) {
            string rest = line.substr(32);
            istringstream iss(rest);
            string cID, sID;
            iss >> cID >> sID;
            cout << totalRev[customer[cID]][sID];
        } else if (line.find("?total_revenue_in_period ") == 0) {
            string startTime, endTime;
            istringstream iss(line.substr(25));
            iss >> startTime >> endTime;
            cout << s[timeStrToInt(endTime)] - (timeStrToInt(startTime) == 0 ? 0 : s[timeStrToInt(startTime) - 1]);
        }
        cout << "\n";
    }

    return 0;
}