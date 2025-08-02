#include <iostream>
#include <iostream>
#include <memory>


// Node representing each element in the linked list
struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// Forward declaration
class SmartPointer;

// Container class managing a linked list
class Container {
    Node* head;
    Node* tail;
    int   count;

public:
    Container() : head(nullptr), tail(nullptr), count(0) {}
    ~Container() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    void add(int value) {
        Node* node = new Node(value);
        if (!head)
            head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
        ++count;
    }

    int size() const { return count; }
    Node* begin() const { return head; }
    Node* end() const { return nullptr; }

    // Grant SmartPointer access to private members if needed
    friend class SmartPointer;
};

// SmartPointer class for iterating and accessing Container
class SmartPointer {
    Node* current;

public:
    SmartPointer(Node* node) : current(node) {}

    // Dereference to access element
    int& operator*() const {
        if (!current) throw std::runtime_error("Dereferencing null SmartPointer!");
        return current->data;
    }

    // Pre-increment to move to next element
    SmartPointer& operator++() {
        if (current) current = current->next;
        return *this;
    }

    // Comparison for iterator-like usage
    bool operator!=(const SmartPointer& other) const {
        return current != other.current;
    }
};


// Custom resource type
struct Resource {
    int id;
    Resource(int id) : id(id) {
        std::cout << "Resource " << id << " created\n";
    }
    ~Resource() {
        std::cout << "Resource " << id << " destroyed\n";
    }
};

// Custom deleter function
void customDeleter(Resource* res) {
    std::cout << "Custom deleter called for Resource " << res->id << "\n";
    delete res;
}

int main1() {
    // 1. Create unique_ptr with custom deleter
    std::unique_ptr<Resource, decltype(&customDeleter)> uniquePtr(new Resource(1), customDeleter);
    
    // 2. Convert unique_ptr to shared_ptr using std::move
    // The custom deleter is automatically transferred
    std::shared_ptr<Resource> sharedPtr = std::move(uniquePtr);
    
    // Verify unique_ptr is now empty
    if (!uniquePtr) {
        std::cout << "uniquePtr is now empty (ownership transferred)\n";
    }
    
    // 3. Create another unique_ptr with custom deleter
    std::unique_ptr<Resource, void(*)(Resource*)> anotherUnique(new Resource(2), 
        [](Resource* res) {
            std::cout << "Lambda deleter called for Resource " << res->id << "\n";
            delete res;
        });
    
    // 4. Convert to shared_ptr with lambda deleter
    std::shared_ptr<Resource> anotherShared = std::move(anotherUnique);
    
    // 5. Create shared_ptr directly with custom deleter
    std::shared_ptr<Resource> directShared(new Resource(3), customDeleter);
    
    std::cout << "--- End of scope ---\n";
    // All shared_ptrs will be destroyed here with their custom deleters
    return 0;
}

int main() {
    Container c;
    c.add(10);
    c.add(20);
    c.add(30);

    std::cout << "List elements using SmartPointer:\n";

    for (SmartPointer it = c.begin(); it != SmartPointer(c.end()); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Example of modification
    SmartPointer it = c.begin();
    ++it; // Move to second element
    *it = 42; // Modify value

    std::cout << "After modifying the second element:\n";
    for (SmartPointer it = c.begin(); it != SmartPointer(c.end()); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    main1();
    return 0;
}
