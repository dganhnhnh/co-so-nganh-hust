#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <algorithm>
using namespace std;

struct Submission {
    string userID;
    string problemID;
    string timeStamp;
    string status;
    int point;
};

string trimSpaces(const string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");

    if (first == string::npos || last == string::npos) {
        // The string is empty or contains only spaces
        return "";
    }

    return str.substr(first, last - first + 1);
}

int main() {
    vector<Submission> submissions;
    unordered_map<string, int> errSubOfUser;
    map<pair<string, string>, int> pointOfUser;
    int totalErrSub = 0;
    // TODO
    unordered_map<string, int> hourlySubmission;

    // Reading operational data
    string line;
    while (getline(cin, line) && line != "#")
    {
        istringstream iss(line);
        Submission sub;
        iss >> sub.userID >> sub.problemID >> sub.timeStamp >> sub.status >> sub.point;
        submissions.push_back(sub);

        if (sub.status == "ERR")
        {
            errSubOfUser[sub.userID]++;
            totalErrSub++;
        }
        else
        {

            auto &userProblemPair = pointOfUser[{sub.userID, sub.problemID}];
            userProblemPair = max(userProblemPair, sub.point);
        }
    }

    sort(submissions.begin(), submissions.end(), [](const Submission &a, const Submission &b)
         { return a.timeStamp < b.timeStamp; });

    unordered_map<string, int> totalPointOfUser;
    for (const auto &[userProblem, point] : pointOfUser)
    {
        totalPointOfUser[userProblem.first] += point;
    }

    // Reading queries
    while (getline(cin, line) && line != "#")
    {
        if (line == "?total_number_submissions")
        {
            cout << submissions.size() << endl;
        }
        else if (line == "?number_error_submision")
        {
            cout << totalErrSub << endl;
        }
        else if (line.find("?number_error_submision_of_user") == 0)
        {
            string userID = line.substr(32);
            userID = trimSpaces(userID);
            cout << errSubOfUser[userID] << endl;
        }
        else if (line.find("?total_point_of_user") == 0)
        {
            string userID = line.substr(21);
            userID = trimSpaces(userID);
            cout << totalPointOfUser[userID] << endl;
        }
        else if (line.find("?number_submission_period") == 0)
        {
            string fromTime, toTime;
            istringstream iss(line.substr(25));
            iss >> fromTime >> toTime;

            int subCount = 0;
            auto startIt = lower_bound(submissions.begin(), submissions.end(), fromTime, [](const Submission &a, const string &b)
                                       { return a.timeStamp < b; });
                                    //    xem lai cai nay
            auto endIt = upper_bound(startIt, submissions.end(), toTime, [](const string &a, const Submission &b)
                                     { return a < b.timeStamp; });

            cout << distance(startIt, endIt) << endl;
        }
    }

    return 0;
}
