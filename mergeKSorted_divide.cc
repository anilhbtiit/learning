#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

/* Takes two lists sorted in increasing order, and 
   merges their nodes together to make one big 
   sorted list and returns head of the merged */
Node* mergeTwo(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->data <= b->data) {
        a->next = mergeTwo(a->next, b);
        return a;
    } else {
        b->next = mergeTwo(a, b->next);
        return b;
    }
}

// The main function that takes an array of 
// lists and generates the sorted output
Node* mergeK(Node* arr[], int k) {
  
    // First merge two adjacent lists, then merge
    // the merged adjacen and so on.
    for (int gap = 1; gap < k; gap *= 2) {
        for (int i = 0; i + gap < k; i += gap * 2) {
            arr[i] = mergeTwo(arr[i], arr[i + gap]);
        }
    }

    return k > 0 ? arr[0] : nullptr;
}

int main() {
    int k = 6;

    Node* arr[k];

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

    arr[3] = new Node(12);
    arr[3]->next = new Node(15);
    arr[3]->next->next = new Node(18);
    arr[3]->next->next->next = new Node(21);

    arr[4] = new Node(13);
    arr[4]->next = new Node(16);
    arr[4]->next->next = new Node(19);
    arr[4]->next->next->next = new Node(22);

    arr[5] = new Node(14);
    arr[5]->next = new Node(17);
    arr[5]->next->next = new Node(20);
    arr[5]->next->next->next = new Node(23);

    Node* head = mergeK(arr, k);
 
    for (Node *node = head; node != nullptr; node = node->next) 
        cout << node->data << " ";

    return 0;
}

