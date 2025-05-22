#include <iostream>
#include <climits>
#include <chrono>
#include <immintrin.h>

// Function to calculate absolute difference using conditional branches
inline int absoluteDifference(int a, int b) {
    if (a >= b) {
        return a - b;
    } else {
        return b - a;
    }
}

inline int aabsoluteDifference(int a, int b) {
    int diff = a - b;
    int mask = diff >> (sizeof(int) * CHAR_BIT - 1);
    return (diff ^ mask) - mask;
}

int main() {
    int x = 10;
    int y = 20;
#if 0
    auto start = std::chrono::high_resolution_clock::now();    

    // Calculate and print absolute difference
    for(int i=0; i < 100000000; ++i) { 
      //std::cout << "Absolute Difference: " << absoluteDifference(x, y) << std::endl;
      absoluteDifference(x, y);
    }
    auto end = std::chrono::high_resolution_clock::now();    
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Total time with if cond : " << duration.count() << " ms" << std::endl;
#else
    auto start = std::chrono::high_resolution_clock::now();    

#if 0
    for(int i=0; i < 100000000; ++i) { 
      //std::cout << "Absolute Difference: " << aabsoluteDifference(x, y) << std::endl;
      aabsoluteDifference(x, y);
    }
#else
#if 0
    float array1[1000];
    float array2[1000];
    float result[1000];
    for (int i = 0; i < 1000; ++i) {
      result[i] = array1[i] + array2[i];
    }
#else

    __m128 vec1, vec2, result;
    // ... (load elements from arrays into vectors)
    result = _mm_add_ps(vec1, vec2);
    // ... (store result vector back to array)
#endif
#endif
    auto end = std::chrono::high_resolution_clock::now();    
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Total time without cond : " << duration.count() << " ms" << std::endl;
#endif
    return 0;
}

