#if 1  //see the diff in 2 results here, if-else
#include <iostream>
#include <unordered_map>
#include <random>
#include <chrono>

constexpr size_t SIMULATED_HASHMAP_SIZE = 1000000; // Smaller size for simulation
constexpr size_t ENTRIES_PER_SECOND = 25000;      // Target entries per second
constexpr double CLOCK_SPEED = 4.0e9;             // 4 GHz clock speed
constexpr int NUM_CORES = 4;                      // Number of cores

// Simulate some dummy computation for each insertion
void simulate_computation() {
    volatile double result = 0;
    for (int i = 0; i < 100; ++i) {
        result += i * 0.001; // Dummy floating-point operations
    }
}

int main() {
    std::unordered_map<size_t, size_t> hashmap; // Do not pre-reserve massive memory

    std::mt19937_64 rng(std::random_device{}()); // Random number generator
    std::uniform_int_distribution<size_t> dist(0, SIMULATED_HASHMAP_SIZE - 1);

    size_t total_insertions = 0;
    auto start_time = std::chrono::high_resolution_clock::now();

    while (true) {
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = current_time - start_time;

        if (elapsed.count() >= 1.0) {
            std::cout << "Entries inserted in 1 second: " << total_insertions << std::endl;
            if (total_insertions >= ENTRIES_PER_SECOND) {
                std::cout << "Simulation successful: Achieved target of " << ENTRIES_PER_SECOND << " entries per second." << std::endl;
            } else {
                std::cout << "Simulation failed: Only " << total_insertions << " entries inserted." << std::endl;
            }
            break;
        }

        // Simulate hashmap insertion
        size_t key = dist(rng);
        size_t value = dist(rng);

        hashmap[key] = value; // Insert key-value pair

        simulate_computation(); // Simulate computation to mimic workload

        ++total_insertions;
    }

    return 0;
}


#else
#include <iostream>
#include <unordered_map>
#include <random>
#include <chrono>

constexpr size_t HASHMAP_SIZE = (10L * 1024 * 1024 * 1024) / sizeof(std::pair<size_t, size_t>); // Approximate hashmap size in elements
constexpr size_t ENTRIES_PER_SECOND = 25000; // Target entries per second
constexpr double CLOCK_SPEED = 4.0e9; // 4 GHz clock speed
constexpr int NUM_CORES = 4; // Number of cores

// Simulate some dummy computation for each insertion
void simulate_computation() {
    volatile double result = 0;
    for (int i = 0; i < 100; ++i) {
        result += i * 0.001; // Dummy floating-point operations
    }
}

int main() {
    std::unordered_map<size_t, size_t> hashmap;
    hashmap.reserve(HASHMAP_SIZE); // Reserve memory for hashmap

    std::mt19937_64 rng(std::random_device{}()); // Random number generator
    std::uniform_int_distribution<size_t> dist(0, HASHMAP_SIZE - 1);

    size_t total_insertions = 0;
    auto start_time = std::chrono::high_resolution_clock::now();

    while (true) {
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = current_time - start_time;

        if (elapsed.count() >= 1.0) {
            std::cout << "Entries inserted in 1 second: " << total_insertions << std::endl;
            if (total_insertions >= ENTRIES_PER_SECOND) {
                std::cout << "Simulation successful: Achieved target of " << ENTRIES_PER_SECOND << " entries per second." << std::endl;
            } else {
                std::cout << "Simulation failed: Only " << total_insertions << " entries inserted." << std::endl;
            }
            break;
        }

        // Simulate hashmap insertion
        size_t key = dist(rng);
        size_t value = dist(rng);

        hashmap[key] = value; // Insert key-value pair

        simulate_computation(); // Simulate computation to mimic workload

        ++total_insertions;
    }

    return 0;
}
#endif
