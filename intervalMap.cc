#include <iostream>
#include <map>
#include <stdexcept>

class IntervalMap {
public:
    // Add a new interval with a specific ID
    void addInterval(int start, int end, int id) {
        if (start >= end) {
            throw std::invalid_argument("Invalid interval");
        }
        intervals[start] = {end, id};
    }

    // Look up a single index
    int lookup(int index) {
        auto it = intervals.upper_bound(index);
        auto it1 = intervals.lower_bound(index);

        if (it == intervals.begin()) {
            throw std::out_of_range("Index out of any interval");
        }
        --it;
        if (it->second.first >= index) {
            return it->second.second;
        }
        throw std::out_of_range("Index out of any interval");
    }

    // Look up a range of indices
    int lookup(int start, int end) {
        if (start >= end) {
            throw std::invalid_argument("Invalid range");
        }
        auto it = intervals.upper_bound(start);
        auto it1 = intervals.lower_bound(start);

        if (it == intervals.begin() || (--it)->second.first < end) {
            throw std::out_of_range("Range out of any interval");
        }
        if (it->first <= start && it->second.first >= end) {
            return it->second.second;
        }
        throw std::out_of_range("Range out of any interval");
    }

private:
    std::map<int, std::pair<int, int>> intervals; // start -> (end, id)
};

int main() {
    IntervalMap imap;

    // Add intervals
    imap.addInterval(3, 9, 10);
    imap.addInterval(10, 15, 20);
    imap.addInterval(0, 2, 30);

    // Look up single indices
    try {
        std::cout << "Lookup N1[2]: " << imap.lookup(3) << std::endl; // Output: 10
        std::cout << "Lookup N1[15]: " << imap.lookup(15) << std::endl; // Output: 20
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    // Look up ranges
    try {
        std::cout << "Lookup N1[4:6]: " << imap.lookup(4, 6) << std::endl; // Output: 10
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::cout << "Lookup N1[9:10]: " << imap.lookup(9, 10) << std::endl; // Output: throws exception
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

