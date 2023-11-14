#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <chrono>
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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input_file.txt output_file.txt" << endl;
        return 1;
    }

    auto start_time = chrono::high_resolution_clock::now();

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cerr << "Error opening output file." << endl;
        return 1;
    }
    vector<Submission> submissions;
    unordered_map<string, int> errSubOfUser;
    map<pair<string, string>, int> pointOfUser;
    int totalErrSub = 0;
    // TODO
    unordered_map<string, int> hourlySubmission;

    // Reading operational data
    string line;
    while (getline(inputFile, line) && line != "#")
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
    while (getline(inputFile, line) && line != "#")
    {
        if (line == "?total_number_submissions")
        {
            outputFile << submissions.size() << endl;
        }
        else if (line == "?number_error_submision")
        {
            outputFile << totalErrSub << endl;
        }
        else if (line.find("?number_error_submision_of_user") == 0)
        {
            string userID = line.substr(32);
            userID = trimSpaces(userID);
            outputFile << errSubOfUser[userID] << endl;
        }
        else if (line.find("?total_point_of_user") == 0)
        {
            string userID = line.substr(21);
            userID = trimSpaces(userID);
            outputFile << totalPointOfUser[userID] << endl;
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

            outputFile << distance(startIt, endIt) << endl;
        }
    }
    auto end_time = chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    // Print the duration
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;


    return 0;
}
