#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int x) : data(x), next(nullptr) {}
};

// returns index of the smallest head list.
// If all lists are empty, then return -1
int getMin(vector<Node *> &arr)
{
    int mi = -1;
    int minVal = INT_MAX;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] != nullptr)
        {
            if (arr[i]->data < minVal)
            {
                minVal = arr[i]->data;
                mi = i;
            }
        }
    }
    return mi;
}

// Function to merge K sorted linked lists
Node *mergeKLists(vector<Node *> &arr)
{
    // Set the head and tail of the result
    // list explicitely to avoid repeated
    // condition checks inside the while
    int mi = getMin(arr);
    if (mi == -1)
        return nullptr;
    Node *head = arr[mi];
    Node *tail = head;
    arr[mi] = arr[mi]->next;

    // Get minimum list head and
    // append it after the tail of
    // result and move ahead in that
    // list
    mi = getMin(arr);
    while (mi != -1) {
        tail->next = arr[mi];
        tail = tail->next;
        arr[mi] = arr[mi]->next;
        mi = getMin(arr);
    }
  
    tail->next = nullptr;
    return head;
}

/* Function to print nodes in a given
   linked list */
void printList(Node *node)
{
    while (node != nullptr)
    {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

// Driver program to test above functions
int main()
{
    int k = 3; // Number of linked lists

    vector<Node *> arr(k);

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

    Node *head = mergeKLists(arr);

    printList(head);

    return 0;
}

