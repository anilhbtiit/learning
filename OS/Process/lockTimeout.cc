#if 1
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;

bool try_lock_for_timeout(std::mutex &mtx, int timeout_seconds) {
    auto start = std::chrono::steady_clock::now();
    while (true) {
        if (mtx.try_lock()) {
            return true; // Successfully acquired lock
        }
        
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - start;
        if (elapsed_seconds.count() >= timeout_seconds) {
            return false; // Timeout reached
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep for a while before retrying
    }
}

void task(int id) {
    if (try_lock_for_timeout(mtx, 2)) {
        std::cout << "Thread " << id << " has acquired the lock." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work
        std::cout << "Thread " << id << " is releasing the lock." << std::endl;
        mtx.unlock();
    } else {
        std::cout << "Thread " << id << " timed out while trying to acquire the lock." << std::endl;
    }
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}


#else

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <unistd.h>
#include <condition_variable>
#include <string.h>

std::mutex mtx;

void task(int id) {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // Defer lock initially

    // Try to acquire the lock with a timeout of 2 seconds
    if (lock.try_lock_for(std::chrono::seconds(2))) {
        std::cout << "Thread " << id << " has acquired the lock." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work
        std::cout << "Thread " << id << " is releasing the lock." << std::endl;
    } else {
        std::cout << "Thread " << id << " timed out while trying to acquire the lock." << std::endl;
    }
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
#endif
