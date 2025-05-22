#include <iostream>
#include <thread>
#include <semaphore>

std::counting_semaphore<3> semaphore(3); // Semaphore with a max count of 3

void access_resource(int thread_id) {
    semaphore.acquire(); // Decrease the count, block if count is 0
    std::cout << "Thread " << thread_id << " is accessing the resource.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << thread_id << " is releasing the resource.\n";
    semaphore.release(); // Increase the count
}

int main() {
    std::thread threads[6];
    for (int i = 0; i < 6; ++i) {
        threads[i] = std::thread(access_resource, i + 1);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}

