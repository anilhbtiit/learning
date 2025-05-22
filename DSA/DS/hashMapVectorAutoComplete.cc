//Build the Hash Map by iterating through a dictionary of words and storing all prefixes for each word as keys.
//For each prefix, store the word in the corresponding list.
//Querying involves looking up the prefix in the Hash Map to get the suggestions.
//

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <chrono>


class Autocomplete {
private:
    std::unordered_map<std::string, std::vector<std::string>> prefixMap;
    //std::unordered_map<std::string, std::set<std::string>> prefixMap;

    // Helper function to generate prefixes for a word
    void addPrefixes(const std::string& word) {
        std::string prefix = "";
        for (char c : word) {
            prefix += c;
            prefixMap[prefix].push_back(word);
            //prefixMap[prefix].insert(word);
        }
    }

    // Remove duplicates and sort suggestions (optional for efficiency)
    void optimizeSuggestions() {
        for (auto& entry : prefixMap) {
            auto& suggestions = entry.second;
            std::sort(suggestions.begin(), suggestions.end());
            suggestions.erase(std::unique(suggestions.begin(), suggestions.end()), suggestions.end());
        }
    }

public:
    // Build the prefix map from a list of words
    void build(const std::vector<std::string>& dictionary) {
        for (const std::string& word : dictionary) {
            addPrefixes(word);
        }
        optimizeSuggestions();
    }

    // Get autocomplete suggestions for a given prefix
    std::vector<std::string> autocomplete(const std::string& prefix) {
    //std::set<std::string> autocomplete(const std::string& prefix) {
        if (prefixMap.find(prefix) != prefixMap.end()) {
            return prefixMap[prefix];
        }
        return {}; // No suggestions
    }
};

using namespace std;

using namespace std::chrono;


// Test the autocomplete feature
int main() {
    auto start = high_resolution_clock::now();

    Autocomplete autocomplete;
    std::vector<std::string> dictionary = {"Hello", "Hell", "Heaven", "Heavy", "Hero", "hermit","Hat","Hen","Heap","Head","Hill","Hint","Heel","Hand","Hook","Home","Host","Hood","Hero","Hall","Habit","Health","Horse","Hunch","Height","Hunger","House","Hassle","Holiday","History"};

    autocomplete.build(dictionary);

    std::string prefix = "H";
    std::vector<std::string> suggestions = autocomplete.autocomplete(prefix);
    //std::set<std::string> suggestions = autocomplete.autocomplete(prefix);


    std::cout << "Autocomplete suggestions for \"" << prefix << "\":\n";
    for (const std::string& suggestion : suggestions) {
        std::cout << suggestion << "\n";
    }
    auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<milliseconds>(stop - start);
    auto duration = duration_cast<nanoseconds>(stop - start);

    cout << "\nTime taken: " << duration.count() << " nanoseconds.\n" << endl;

    return 0;
}

