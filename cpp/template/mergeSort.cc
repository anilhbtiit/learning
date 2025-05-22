#include <stdio.h>
#include <stdlib.h>
#include "template.h"

//using namespace N;
// Function to split a linked list<int> into two halves
void splitlist(N::list<int>* source, N::list<int>** front, N::list<int>** back) {
  N::list<int>* slow = source;
  N::list<int>* fast = source->getNextNode();

    while (fast != NULL) {
        fast = fast->getNextNode();
        if (fast != NULL) {
            slow = slow->getNextNode();
            fast = fast->getNextNode();
        }
    }

    *front = source;
    *back = slow->getNextNode();
    slow->setNextNode(NULL);
}

// Function to merge two sorted linked list<int>s
N::list<int>* mergeSortedlists(N::list<int>* a, N::list<int>* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    N::list<int>* result = NULL;

    if (a->getVal() <= b->getVal()) {
        result = a;
        result->setNextNode(mergeSortedlists(a->getNextNode(), b));
    } else {
        result = b;
        result->setNextNode(mergeSortedlists(a, b->getNextNode()));
    }

    return result;
}

// Function to sort a linked list<int> using Merge Sort
//template <typename T>
void mergeSort(N::list<int>** head) {
    N::list<int>* current = *head;
    N::list<int>* front;
    N::list<int>* back;

    if (current == NULL || current->getNextNode() == NULL) {
        return;
    }

    splitlist(current, &front, &back);

    mergeSort(&front);
    mergeSort(&back);

    *head = mergeSortedlists(front, back);
}

