#include <bits/stdc++.h>

using namespace std;

const int MAXINT = (int)1e5 + 5;
unordered_map<string, int> errorSubmissionOfUser;
unordered_map<string, int> pointOfUser;
long long submissionCount[24 * 60 * 60];
map<pair<string, string>, int> pointProblem;
unordered_map<string, int> totalPointOfUser;

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
    int numSub = 0;
    int numErrorSub = 0;
    while (true)
    {
        string userID, problemID, timePoint, status;
        int point;
        cin >> userID;
        if (userID == "#")
            break;
        cin >> problemID >> timePoint >> status ;
        cin >> point;
        submissionCount[timeStrToInt(timePoint)]++;
        numSub++;
        if (status == "OK"){
            // cout << pointOfUser[userID]<< endl<<point <<endl;
            // pointOfUser[userID] += max(pointOfUser[userID], point);
            // cout << "OK\n";
            auto& userProblemPair = pointProblem[{userID, problemID}];
            userProblemPair = max(userProblemPair, point);
        }
        else if (status == "ERR")
        {
            errorSubmissionOfUser[userID]++;
            numErrorSub++;
            // cout << numErrorSub<< endl;
        }
    }
    for (int i = 1; i < 24 * 60 * 60; ++i)
        submissionCount[i] += submissionCount[i - 1];

    for (const auto& [userProblem, point] : pointProblem) {
        totalPointOfUser[userProblem.first] += point;
    }
    while (true)
    {
        string type;
        cin >> type;
        if (type == "#")
            break;
        if (type == "?total_number_submissions")
            cout << numSub;
        if (type == "?number_error_submision")
        {
            cout << numErrorSub;
        }
        if (type == "?number_error_submision_of_user")
        {
            string userID;
            cin >> userID;
            // cout << "|"<< userID<< "|";
            cout << errorSubmissionOfUser[userID];
        }
        if (type == "?total_point_of_user")
        {
            string userID;
            cin >> userID;
            // cout << "|"<< userID<< "|";
            cout << totalPointOfUser[userID];
        }
        if (type == "?number_submission_period")
        {
            string start, end;
            cin >> start >> end;
            cout << submissionCount[timeStrToInt(end)] - (timeStrToInt(start) == 0 ? 0 : submissionCount[timeStrToInt(start) - 1]);
        }
        cout << "\n";
    }
    return 0;
}
