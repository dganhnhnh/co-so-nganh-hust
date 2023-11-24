#include <bits/stdc++.h>

using namespace std;

const int MAXINT = (int)1e5 + 5;
unordered_map<string, int> customerShopRevenue;
unordered_map<string, int> totalRev[MAXINT];
unordered_map<string, int> rev;
long long revenueUntil[24 * 60 * 60];

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

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long totalRevenue = 0;
    int numOrder = 0;
    int numCustomer = 0;
    while (true)
    {
        string cID, pID, sID, timePoint;
        int price;
        cin >> cID;
        if (cID == "#")
            break;
        cin >> pID >> price >> sID >> timePoint;
        revenueUntil[timeStrToInt(timePoint)] += price;
        totalRevenue += 1LL * price;
        numOrder++;
        if (customerShopRevenue[cID] == 0)
        {
            customerShopRevenue[cID] = ++numCustomer;
        }
        totalRev[customerShopRevenue[cID]][sID] += price;
        rev[sID] += price;
    }
    for (int i = 1; i < 24 * 60 * 60; ++i)
        revenueUntil[i] += revenueUntil[i - 1];

    while (true)
    {
        string type;
        cin >> type;
        if (type == "#")
            break;
        if (type == "?total_number_orders")
            cout << numOrder;
        if (type == "?total_revenue")
            cout << totalRevenue;
        if (type == "?revenue_of_shop")
        {
            string sID;
            cin >> sID;
            cout << rev[sID];
        }
        if (type == "?total_consume_of_customer_shop")
        {
            string cID, sID;
            cin >> cID >> sID;
            cout << totalRev[customerShopRevenue[cID]][sID];
        }
        if (type == "?total_revenue_in_period")
        {
            string start, end;
            cin >> start >> end;
            cout << revenueUntil[timeStrToInt(end)] - (timeStrToInt(start) == 0 ? 0 : revenueUntil[timeStrToInt(start) - 1]);
        }
        cout << "\n";
    }
    return 0;
}