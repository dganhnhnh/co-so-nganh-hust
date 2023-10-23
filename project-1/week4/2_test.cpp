#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); // Seed the random number generator with the current time

    int test_cases = 10; // Number of test cases to generate

    for (int t = 0; t < test_cases; t++) {
        int n = 1 + rand() % 100; // You can adjust the range for n as needed
        cout << n << endl;
        for (int i = 0; i < n; i++) {
            int Ai = 1 + rand() % 100; // You can adjust the range for Ai as needed
            cout << Ai << " ";
        }
        cout << endl;
    }

    return 0;
}
