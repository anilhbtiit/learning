#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <chrono>

const int BUFFER_SIZE = 10;      // Maximum buffer size
const int CHUNK_SIZE = 3;       // Consumer chunk size
std::queue<int> buffer;         // Shared buffer
std::mutex mtx;                 // Mutex for synchronization
std::condition_variable cv;     // Condition variable

void producer() {
    int item = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        while (buffer.size() >= BUFFER_SIZE) {
            cv.wait(lock); // Wait if buffer is full
        }

        // Produce items
        int items_to_produce = std::min(BUFFER_SIZE - (int)buffer.size(), CHUNK_SIZE);
        for (int i = 0; i < items_to_produce; ++i) {
            buffer.push(item++);
            std::cout << "Produced: " << item << std::endl;
        }
        
        cv.notify_all(); // Notify consumer
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        while (buffer.size() < CHUNK_SIZE) {
            cv.wait(lock); // Wait if insufficient items to consume
        }

        // Consume items
        std::cout << "Consuming chunk: ";
        for (int i = 0; i < CHUNK_SIZE; ++i) {
            std::cout << buffer.front() << " ";
            buffer.pop();
        }
        std::cout << std::endl;

        cv.notify_all(); // Notify producer
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons(consumer);

    prod.join();
    cons.join();

    return 0;
}

