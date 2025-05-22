#include <iostream>
#include <map>
#include <string>

int main() {
    // Create a std::map with int keys and std::string values
    std::map<int, std::string> myMap;

    // Insert key-value pairs using operator[]
    myMap[5] = "five";
    myMap[1] = "one";
    myMap[3] = "three";

    // Insert key-value pairs using insert() method
    auto result = myMap.insert(std::make_pair(2, "two"));
    if (result.second) {
        std::cout << "Inserted successfully: " << result.first->first << " -> " << result.first->second << std::endl;
    } else {
        std::cout << "Insertion failed for key 2" << std::endl;
    }

    // Insert another pair
    myMap.insert({4, "four"});

    // Attempt to insert a duplicate key
    result = myMap.insert({3, "three again"});
    if (result.second) {
        std::cout << "Inserted successfully: " << result.first->first << " -> " << result.first->second << std::endl;
    } else {
        std::cout << "Insertion failed for key 3" << std::endl;
    }

    // Print the contents of the map
    std::cout << "Map contents:" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }

    // Erase an element by key
    myMap.erase(3);

    // Print the map contents after erasing
    std::cout << "Map contents after erasing key 3:" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }

    return 0;
}

