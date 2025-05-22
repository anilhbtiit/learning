#define CDE

#ifndef ABC

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <string>
#include <cassert>

void generateMatrix(int rows, int cols, std::vector<std::vector<int>>& matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100; // Generate random integers between 0 and 99
        }
    }
}

void printMatrix(int rows, int cols, const std::vector<std::vector<int>>& matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

std::pair<int,int> 
find(int rows, int cols, int x, int y, const std::vector<std::vector<int>>& matrix) {
  int value = 0, index = 0;
  std::vector<int> flat_matrix;
  for (const auto& row : matrix) {
    flat_matrix.insert(flat_matrix.end(), row.begin(), row.end());
  }
  //index = (cols*(x-1))+(y-1);
  if(x < rows && y < cols) {
    value = matrix[x][y];
    index = (cols*(x))+(y);
    assert(value==flat_matrix[index]);
  } else {
    std::cout << "\nOut of bound array access";
  }
  return std::make_pair(value, index);
}


int main() {
    int rows, cols;

    // Seed random number generator
    srand(time(NULL));

    // Input dimensions of the matrix
    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    // Declare the matrix
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

    // Generate and print the matrix
    generateMatrix(rows, cols, matrix);
    std::cout << "Generated 2D Matrix:" << std::endl;
    int x, y;
    printMatrix(rows, cols, matrix);
    std::cout << "\n" << "Find value at " << "\n";
    std::cout << "row: ";
    std::cin >> x;
    std::cout << "\ncol: ";
    std::cin >> y;
    std::pair <int,int> pair = find(rows, cols, x, y, matrix);
    std::cout << "\n value: " << pair.first << ", Index in flat arr: " << pair.second ;
    return 0;
}

#elif defined(CDE)

#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAX_ROWS = 100;
const int MAX_COLS = 100;

void generateMatrix(int rows, int cols, int matrix[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void printMatrix(int rows, int cols, int matrix[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    int rows, cols;

    srand(time(NULL));

    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    if (rows > MAX_ROWS || cols > MAX_COLS) {
        std::cerr << "Error: Exceeded maximum matrix size." << std::endl;
        return 1;
    }

    int matrix[MAX_ROWS][MAX_COLS];

    generateMatrix(rows, cols, matrix);
    std::cout << "Generated 2D Matrix:" << std::endl;
    printMatrix(rows, cols, matrix);

    return 0;
}



#else

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100; // Generate random integers between 0 and 99
        }
    }
}

void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows, cols;

    // Seed random number generator
    srand(time(NULL));

    // Input dimensions of the matrix
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    // Declare the matrix
    int matrix[rows][cols];

    // Generate and print the matrix
    generateMatrix(rows, cols, matrix);
    printf("Generated 2D Matrix:\n");
    printMatrix(rows, cols, matrix);

    return 0;
}
#endif
