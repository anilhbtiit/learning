#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// Traditional Quick Sort Algorithm
int partition(vector<int>& v, int l, int r) {
    int p = v[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (v[j] < p) {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[r]);
    return i + 1;
}
void quickSort(vector<int>& v, int l, int r) {
    if (l < r) {
        int pi = partition(v, l, r);
        quickSort(v, l, pi - 1);
        quickSort(v, pi + 1, r);
    }
}

int main() {
  
    // Array with 1 million random elements
    const int n = 1000000;
    vector<int> data(n);
    for (int& val : data) {
        val = rand() % 1000;
    }
      time_point<high_resolution_clock> start, end;

    // Measure time for traditional Quick Sort
    vector<int> qSortData = data;
    start = high_resolution_clock::now();
    quickSort(qSortData, 0, n - 1);
    //for(int& d:qSortData) {
    //  std::cout << d << "\t";
    //}
    end = high_resolution_clock::now();
    auto d = duration_cast<milliseconds>(end - start);
    cout << "Traditional Quick Sort: " << d.count() << " ms\n";

    // Measure time for STL sort() function
    vector<int> sortData = data;
    start = high_resolution_clock::now();
    sort(sortData.begin(), sortData.end());
    end = high_resolution_clock::now();
    d = duration_cast<milliseconds>(end - start);
    cout << "STL sort(): " << d.count() << " ms";

    return 0;
}
