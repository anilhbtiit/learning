

//https://www.usenix.org/publications/loginonline/sieve-cache-eviction-can-be-simple-effective-and-scalable#reference-4


#include <iostream>
#include <unordered_map>
#include <list>
#include <ctime>
using namespace std;

class SieveCache {
private:
    struct CacheEntry {
        int key;
        int value;
        int accessCount; // Metadata: access frequency
        time_t timestamp; // Metadata: last accessed time
    };

    int capacity;
    int threshold; // Access frequency threshold for retention
    unordered_map<int, list<CacheEntry>::iterator> cacheMap; // Key -> List iterator
    list<CacheEntry> cacheList; // Doubly linked list of cache entries

    void applySievePolicy() {
        for (auto it = cacheList.begin(); it != cacheList.end();) {
            if (it->accessCount < threshold) {
                cacheMap.erase(it->key);
                it = cacheList.erase(it);
            } else {
                ++it;
            }
        }
    }

public:
    SieveCache(int capacity, int threshold) : capacity(capacity), threshold(threshold) {}

    int get(int key) {
        if (cacheMap.find(key) != cacheMap.end()) {
            auto it = cacheMap[key];
            it->accessCount++;
            it->timestamp = time(nullptr); // Update access time
            return it->value;
        }
        return -1; // Key not found
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            auto it = cacheMap[key];
            it->value = value;
            it->accessCount++;
            it->timestamp = time(nullptr); // Update access time
        } else {
            if (cacheList.size() >= capacity) {
                applySievePolicy(); // Apply filtering rules
                if (cacheList.size() >= capacity) {
                    auto last = cacheList.back();
                    cacheMap.erase(last.key);
                    cacheList.pop_back();
                }
            }
            cacheList.push_front({key, value, 1, time(nullptr)});
            cacheMap[key] = cacheList.begin();
        }
    }

    void printCache() {
        cout << "Cache Contents: ";
        for (auto& entry : cacheList) {
            cout << "(" << entry.key << ": " << entry.value << ", freq: " << entry.accessCount << ") ";
        }
        cout << endl;
    }
};

int main() {
    SieveCache sieveCache(3, 2); // Capacity = 3, Threshold = 2

    sieveCache.put(1, 10);
    sieveCache.put(2, 20);
    sieveCache.put(3, 30);
    sieveCache.printCache();

    sieveCache.get(1);
    sieveCache.get(2);
    sieveCache.printCache();

    sieveCache.put(4, 40);
    sieveCache.printCache();

    sieveCache.get(1);
    sieveCache.put(5, 50);
    sieveCache.printCache();

    return 0;
}

