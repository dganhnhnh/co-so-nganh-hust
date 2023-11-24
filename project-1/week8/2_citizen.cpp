 #include <bits/stdc++.h>

using namespace std;

const int MAXYEAR = 30001232;
long bornAt[MAXYEAR];
long long bornUntil[MAXYEAR];
//  code and isAlive
unordered_map<string, bool> personAlive;
unordered_map<string, int> mostAliveAncestor;
int maxDepth = 0;
// set<string> rootSet;
unordered_map<int, vector<string>> generation;

int ord(char c)
{
    return c - '0';
}

int dateStrToInt(string date)
{
    int day = ord(date[8]) * 10 + ord(date[9]);
    int month = ord(date[5]) * 10 + ord(date[6]);
    int year = ord(date[0]) * 1000 + ord(date[1]) * 100 + ord(date[2]) * 10 + ord(date[3]);
    return day + month * 100 + year * 10000;
}

int maxUnrelated()
{
    int subset1=0, subset2=0;
    for (int i = 0; i <= maxDepth; ++i)
    {
        if (i % 2 == 0)
        {
            subset1 += generation[i].size();
        }
        else
        {
            subset2 += generation[i].size();
        }
    }
    return max(subset1, subset2);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int numPeople = 0;
    while (true)
    {
        string code, date_of_birth, father_code, mother_code, is_alive, region_code;
        cin >> code;
        if (code == "*")
            break;
        cin >> date_of_birth >> father_code >> mother_code >>  is_alive>> region_code;
        bornAt[dateStrToInt(date_of_birth)]++;
        numPeople++;
        personAlive[code] = is_alive == "Y";
        if (father_code != "0000000" and personAlive[father_code])
        {
            mostAliveAncestor[code] = mostAliveAncestor[father_code] + 1;
            maxDepth = max(maxDepth, mostAliveAncestor[code]);
        }
        if (mother_code != "0000000" and personAlive[mother_code])
        {
            mostAliveAncestor[code] = max(mostAliveAncestor[code], mostAliveAncestor[mother_code] + 1);
            maxDepth = max(maxDepth, mostAliveAncestor[code]);
        }
        generation[mostAliveAncestor[code]].push_back(code);
    }

    for (int i = 0; i < MAXYEAR; ++i){
        bornUntil[i] = bornAt[i];
    }
    for (int i = 1; i < MAXYEAR; ++i){
        bornUntil[i] += bornUntil[i - 1];
    }

    while (true)
    {
        string type;
        cin >> type;
        if (type == "***")
            break;
        if (type == "NUMBER_PEOPLE")
            cout << numPeople;
        if (type == "NUMBER_PEOPLE_BORN_AT")
        {
            string date;
            cin >> date;
            // cout << dateStrToInt(date);
            cout << bornAt[dateStrToInt(date)];
        }
        if (type == "NUMBER_PEOPLE_BORN_BETWEEN")
        {
            string start, end;
            cin >> start >> end;
            cout << bornUntil[dateStrToInt(end)] - (dateStrToInt(start) == 0 ? 0 : bornUntil[dateStrToInt(start) - 1]);

        }
        if (type == "MOST_ALIVE_ANCESTOR")
        {
            // father and mother are input before child
            string code;
            cin >> code;
            cout << mostAliveAncestor[code];
        }
        if (type == "MAX_UNRELATED_PEOPLE")
        {
            cout << maxUnrelated();
        }
        cout << "\n";
    }
    return 0;
}
