#include <iostream>
#include <unordered_map>
using namespace std;

// Node structure for the doubly linked list
struct Node {
    int key, value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache; // Hash map: Key -> Node
    Node* head; // Most recently used
    Node* tail; // Least recently used

    // Add node to the head of the doubly linked list
    void addNode(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    // Remove a node from the doubly linked list
    void removeNode(Node* node) {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    // Move a node to the head
    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }

    // Remove the tail node
    Node* popTail() {
        Node* lruNode = tail->prev;
        removeNode(lruNode);
        return lruNode;
    }

public:
    LRUCache(int cap) : capacity(cap) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Get the value of a key
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            moveToHead(node);
            return node->value;
        }
        return -1; // Key not found
    }

    // Insert or update a key-value pair
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addNode(newNode);

            if (cache.size() > capacity) {
                Node* tailNode = popTail();
                cache.erase(tailNode->key);
                delete tailNode;
            }
        }
    }
};

int main() {
    LRUCache lruCache(2); // Capacity: 2

    lruCache.put(1, 1);
    lruCache.put(2, 2);
    cout << "Get 1: " << lruCache.get(1) << endl; // Returns 1
    lruCache.put(3, 3); // Evicts key 2
    cout << "Get 2: " << lruCache.get(2) << endl; // Returns -1 (not found)
    lruCache.put(4, 4); // Evicts key 1
    cout << "Get 1: " << lruCache.get(1) << endl; // Returns -1 (not found)
    cout << "Get 3: " << lruCache.get(3) << endl; // Returns 3
    cout << "Get 4: " << lruCache.get(4) << endl; // Returns 4

    return 0;
}

