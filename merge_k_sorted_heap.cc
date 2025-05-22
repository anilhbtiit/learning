#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

// Comparator used for the priority queue 
// to maintain a min-heap
struct compare {
    bool operator()(Node* a, Node* b) {
        return a->data > b->data;
    }
};

// Function to merge k sorted linked lists
Node* mergeLists(vector<Node*>& arr) {
  
    // Priority queue (min-heap)
    priority_queue<Node*, vector<Node*>, compare> pq;

    // Push the head nodes of all the k lists 
    // into the priority queue
    for (Node* node : arr) {
        if (node != nullptr) {
            pq.push(node);
        }
    }

    // Handles the case when all lists are empty
    if (pq.empty()) return nullptr;

    // Dummy node to simplify edge cases
    Node* dummy = new Node(0); 
    Node* tail = dummy;

    // Process the nodes in the priority queue
    while (!pq.empty()) {
        Node* curr = pq.top();
        pq.pop();

        // Add the top element of pq to the merged list
        tail->next = curr;
        tail = tail->next;

        // If there is a next node in the 
        // current list, push it into the pq
        if (curr->next != nullptr) {
            pq.push(curr->next);
        }
    }

    Node* head = dummy->next;
    delete dummy; // Free the dummy node
    return head;
}

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    int k = 3; 

    vector<Node*> arr(k);

    arr[0] = new Node(1);
    arr[0]->next = new Node(3);
    arr[0]->next->next = new Node(5);
    arr[0]->next->next->next = new Node(7);

    arr[1] = new Node(2);
    arr[1]->next = new Node(4);
    arr[1]->next->next = new Node(6);
    arr[1]->next->next->next = new Node(8);

    arr[2] = new Node(0);
    arr[2]->next = new Node(9);
    arr[2]->next->next = new Node(10);
    arr[2]->next->next->next = new Node(11);

    Node* head = mergeLists(arr);

    printList(head);

    return 0;
}

