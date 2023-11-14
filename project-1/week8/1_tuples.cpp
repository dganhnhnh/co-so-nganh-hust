#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <tuple>

using namespace std;

using Submission = tuple<string, string, string, string, int>;

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
        iss >> get<0>(sub) >> get<1>(sub) >> get<2>(sub) >> get<3>(sub) >> get<4>(sub);
        submissions.push_back(sub);

        if (get<3>(sub) == "ERR")
        {
            errSubOfUser[get<0>(sub)]++;
            totalErrSub++;
        }
        else
        {
            auto &userProblemPair = pointOfUser[{get<0>(sub), get<1>(sub)}];
            userProblemPair = max(userProblemPair, get<4>(sub));
        }
    }

    sort(submissions.begin(), submissions.end(), [](const Submission &a, const Submission &b)
         { return get<2>(a) < get<2>(b); });

    unordered_map<string, int> totalPointOfUser;
    for (const auto &[userProblem, point] : pointOfUser)
    {
        totalPointOfUser[get<0>(userProblem)] += point;
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
                                       { return get<2>(a) < b; });
            auto endIt = upper_bound(submissions.begin(), submissions.end(), toTime, [](const string &a, const Submission &b)
                                     { return a < get<2>(b); });

            cout << distance(startIt, endIt) << endl;
        }
    }

    return 0;
}
