#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1, mtx2;

void task1() {
    std::lock(mtx1, mtx2); // Lock both mutexes at once
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);  // Lock mtx1
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);  // Lock mtx2

    std::cout << "Task 1 has acquired both locks." << std::endl;
    // Perform critical section work here
}

void task2() {
    std::lock(mtx1, mtx2); // Lock both mutexes at once
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);  // Lock mtx1
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);  // Lock mtx2

    std::cout << "Task 2 has acquired both locks." << std::endl;
    // Perform critical section work here
}

int main() {
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();

    return 0;
}

