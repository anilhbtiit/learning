#include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int>& arr) {
    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    // Step 1: Create count array and initialize to 0
    std::vector<int> count(range, 0);

    // Step 2: Count occurrences of each element
    for (int num : arr) {
        count[num - minVal]++;
    }

    // Step 3: Compute prefix sum
    for (size_t i = 1; i < count.size(); ++i) {
        count[i] += count[i - 1];
    }

    // Step 4: Build the output array
    std::vector<int> output(arr.size());
    for (int i = arr.size() - 1; i >= 0; --i) { // Traverse in reverse for stability
        int num = arr[i];
        output[count[num - minVal] - 1] = num;
        count[num - minVal]--;
    }

    // Step 5: Copy sorted output to the original array
    arr = output;
}

int main() {
    std::vector<int> arr = {14, 22,32, 48, 36, 514, 23, 15, 55, 355, 20};
    std::cout << "Original array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    countingSort(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}

