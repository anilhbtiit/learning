//The heap sort algorithm consists of two phases. In the first phase, the array is converted into a max heap. And in the second phase, the highest element is removed (i.e., the one at the tree root) and the remaining elements are used to create a new max heap. 


#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// Implementation of heapsort
void heapify(vector<int>& v, int n, int i) {
    int m = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && v[l] > v[m])
        m = l;
    if (r < n && v[r] > v[m])
        m = r;
    if (m != i) {
        swap(v[i], v[m]);
        heapify(v, n, m);
    }
}
void heapSort(vector<int>& v) {
    int n = v.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);
    //for(int& d:v)
    //  std::cout << d << "\t";
    //std::cout << "\n";
    for (int i = n - 1; i > 0; i--) {
        swap(v[0], v[i]);
        heapify(v, i, 0);
    }
}

int main() {
    // Array with 1 million random elements
    const int n = 10;//00000;
    vector<int> v(n);
    for (int& val : v)
        val = rand() % 1000;
  
    time_point<high_resolution_clock> start, end;

    // Measure time for Heap Sort
    vector<int> heapSortData = v;
    start = high_resolution_clock::now();
    heapSort(heapSortData);
    for(int& d: heapSortData) {
      std::cout << d << "\t";
    }
    end = high_resolution_clock::now();
    auto d = duration_cast<milliseconds>(end - start);
    cout << "Heap Sort: " << d.count() << " ms\n";

    // Measure time for STL sort() function
    vector<int> sortData = v;
    start = high_resolution_clock::now();
    sort(sortData.begin(), sortData.end());
    end = high_resolution_clock::now();
    d = duration_cast<milliseconds>(end - start);
    cout << "STL sort(): " << d.count() << " ms\n";

    return 0;
}
