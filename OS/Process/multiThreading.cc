//example of using multiple threads to compute the sum of an array in parallel

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

// Shared variables
std::mutex mtx; // Mutex for synchronization
long long global_sum = 0; // Shared sum

// Function to calculate partial sum
void partial_sum(const std::vector<int>& data, int start, int end) {
    long long local_sum = 0;
    for (int i = start; i < end; ++i) {
        local_sum += data[i];
    }

    // Synchronize access to global_sum
    std::lock_guard<std::mutex> lock(mtx);
    global_sum += local_sum;
}

int main() {
    // Input data
    const int data_size = 1000;
    const int num_threads = 4;
    std::vector<int> data(data_size, 1); // Array of size 1000, all elements are 1

    // Divide the work
    int chunk_size = data_size / num_threads;
    std::vector<std::thread> threads;

    // Create threads
    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? data_size : start + chunk_size;
        threads.emplace_back(partial_sum, std::ref(data), start, end);
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    // Output the result
    std::cout << "Total Sum: " << global_sum << std::endl;

    return 0;
}

