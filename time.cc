#include <iostream>
#include <chrono>
#include <thread> // For simulating some workload

using namespace std;
using namespace std::chrono;

int main() {
    // Record the starting time
    auto start = high_resolution_clock::now();

    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Sleep for 500ms

    // Record the ending time
    auto stop = high_resolution_clock::now();

    // Calculate the duration
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    return 0;
}

