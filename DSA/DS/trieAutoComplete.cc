#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

    void collectSuggestions(TrieNode* node, const std::string& prefix, std::vector<std::string>& suggestions) {
        if (!node) return;

        if (node->isEndOfWord) {
            suggestions.push_back(prefix);
        }

        for (const auto& pair : node->children) {
            collectSuggestions(pair.second, prefix + pair.first, suggestions);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    // Insert a word into the Trie
    void insert(const std::string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    // Get autocomplete suggestions for a given prefix
    std::vector<std::string> autocomplete(const std::string& prefix) {
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return {}; // No suggestions
            }
            current = current->children[c];
        }

        std::vector<std::string> suggestions;
        collectSuggestions(current, prefix, suggestions);
        return suggestions;
    }
};

// Test the Trie-based autocomplete
int main() {
    Trie trie;
    trie.insert("hello");
    trie.insert("hell");
    trie.insert("heaven");
    trie.insert("heavy");

    std::string prefix = "he";
    std::vector<std::string> suggestions = trie.autocomplete(prefix);

    std::cout << "Autocomplete suggestions for \"" << prefix << "\":\n";
    for (const std::string& suggestion : suggestions) {
        std::cout << suggestion << "\n";
    }

    return 0;
}

