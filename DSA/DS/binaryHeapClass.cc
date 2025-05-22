#include <iostream>
#include <vector>

using namespace std;

// Priority queue implementation in C++
template<typename T>
class PriorityQueue {
  private:
  vector<T> data;

  public:
  // Implementing Priority Queue using inbuilt available vector in C++
  PriorityQueue() {}

  // Element Inserting function
  void Enqueue(T item) {
    // item Insertion
    data.push_back(item);
    int ci = data.size() - 1;

    // Re-structure heap(Max Heap) so that after 
    // addition max element will lie on top of pq
    while (ci > 0) {
      int pi = (ci - 1) / 2;
      if (data[ci] <= data[pi])
        break;
      T tmp = data[ci];
      data[ci] = data[pi];
      data[pi] = tmp;
      ci = pi;
    }
  }

  T Dequeue() {
    // deleting top element of pq
    int li = data.size() - 1;
    T frontItem = data[0];
    data[0] = data[li];
    data.pop_back();

    --li;
    int pi = 0;

    // Re-structure heap(Max Heap) so that after 
    // deletion max element will lie on top of pq
    while (true) {
      int ci = pi * 2 + 1;
      if (ci > li)
        break;
      int rc = ci + 1;
      if (rc <= li && data[rc] > data[ci])
        ci = rc;
      if (data[pi] >= data[ci])
        break;
      T tmp = data[pi];
      data[pi] = data[ci];
      data[ci] = tmp;
      pi = ci;
    }
    return frontItem;
  }

  // Function which returns peek element
  T Peek() {
    T frontItem = data[0];
    return frontItem;
  }

  int Count() {
    return data.size();
  }
};

// Driver code
int main()
{
  
  // Basic functionality sample of Priority Queue

  // Creating priority queue which contains int in it
  PriorityQueue<int> pq;

  // Insert element 1 in pq
  pq.Enqueue(1);

  cout << "Size of pq is : " << pq.Count() << 
    " and Peek Element is : " << pq.Peek() << endl;

  // Insert element 10 and -8 in pq
  pq.Enqueue(10);
  pq.Enqueue(-8);

  cout << "Size of pq is : " << pq.Count() << 
    " and Peek Element is : " << pq.Peek() << endl;

  // Delete element from pq
  pq.Dequeue();

  cout << "Size of pq is : " << pq.Count() << 
    " and Peek Element is : " << pq.Peek() << endl;

  // Delete element from pq
  pq.Dequeue();

  cout << "Size of pq is : " << pq.Count() << 
    " and Peek Element is : " << pq.Peek() << endl;

  // Insert element 25 in pq
  pq.Enqueue(25);

  cout << "Size of pq is : " << pq.Count() << 
    " and Peek Element is : " << pq.Peek() << endl;

  return 0;
}

// This code is modified by Susobhan Akhuli
