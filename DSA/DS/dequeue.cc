#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;     // Array to store deque elements
    int front;     // Index of the front element
    int rear;      // Index of the rear element
    int capacity;  // Maximum capacity of the deque
    int size;      // Current number of elements
} Deque;

// Function to create a deque with given capacity
Deque* createDeque(int capacity) {
    Deque *deque = (Deque *)malloc(sizeof(Deque));
    deque->data = (int *)malloc(capacity * sizeof(int));
    deque->front = -1;
    deque->rear = 0;
    deque->capacity = capacity;
    deque->size = 0;
    return deque;
}

// Check if the deque is empty
int isEmpty(Deque *deque) {
    return deque->size == 0;
}

// Check if the deque is full
int isFull(Deque *deque) {
    return deque->size == deque->capacity;
}

// Add element to the front
void pushFront(Deque *deque, int value) {
    if (isFull(deque)) {
        printf("Deque is full!\n");
        return;
    }
    deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;
    deque->data[deque->front] = value;
    deque->size++;
    if (deque->size == 1)
        deque->rear = deque->front; // Align rear in case of first push
}

// Add element to the rear
void pushBack(Deque *deque, int value) {
    if (isFull(deque)) {
        printf("Deque is full!\n");
        return;
    }
    deque->rear = (deque->rear + 1) % deque->capacity;
    deque->data[deque->rear] = value;
    deque->size++;
}

// Remove element from the front
void popFront(Deque *deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty!\n");
        return;
    }
    deque->front = (deque->front + 1) % deque->capacity;
    deque->size--;
}

// Remove element from the rear
void popBack(Deque *deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty!\n");
        return;
    }
    deque->rear = (deque->rear - 1 + deque->capacity) % deque->capacity;
    deque->size--;
}

// Get the front element
int getFront(Deque *deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return deque->data[deque->front];
}

// Get the rear element
int getBack(Deque *deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return deque->data[deque->rear];
}

// Free memory
void freeDeque(Deque *deque) {
    free(deque->data);
    free(deque);
}

// Test the deque implementation
int main() {
    Deque *deque = createDeque(5);

    pushFront(deque, 10);
    pushBack(deque, 20);
    pushFront(deque, 5);

    printf("Front: %d\n", getFront(deque));
    printf("Rear: %d\n", getBack(deque));

    popFront(deque);
    printf("After popFront, Front: %d\n", getFront(deque));

    popBack(deque);
    printf("After popBack, Rear: %d\n", getBack(deque));

    freeDeque(deque);
    return 0;
}

