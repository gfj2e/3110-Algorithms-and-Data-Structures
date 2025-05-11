#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>
#include "parameters.h"
using namespace std;

int Fibonacci(int n);
int Sum(int n);
int Largest(const int array[], int size);
void FindEagle(vector<vector<int>>&grid, int rows, int cols);
int FindEagles(vector<vector<int>>&grid, int x, int y);

int main(void) {

    int fibResult = Fibonacci(FibVal);                              // Get results for each function
    int sumResult = Sum(SumVal);
    int largest = Largest(LongestVal, 13);

    cout << "Fibonacci is: " << fibResult << "\n";                  // Print out the results
    cout << "Sum is: " << sumResult << "\n";
    cout << "Largest value of the array is: " << largest << "\n\n";

    ifstream file("eagle.dat");                                     // Open the eagle.dat file
    assert(file);
    
    int rows, cols;
    while (file >> rows >> cols) {                                  // Read the grid into a 2D vector
        vector<vector<int>> eagleGrid(rows, vector<int>(cols));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                file >> eagleGrid[i][j];
            }
        }

        for (int i = 0; i < rows; i++) {                            // Print out the grid
            for (int j = 0; j < cols; j++) {
                cout << eagleGrid[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        FindEagle(eagleGrid, rows, cols);                           // Find the eagles in the grid
    }

    return 0;
}

/*
A function that recusively calculates the fibonacci number of a given
number n. Does the forumla (n-2) + (n-1)
*/
int Fibonacci(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return Fibonacci(n - 2) + Fibonacci(n - 1);
    }
}

/*
A function that recursively calls the Sum function to calculate sum of integers
1, 2, 3,..., n for a given number. sum(n) = n + sum(n - 1)
*/
int Sum(int n) {
    if (n == 0) {
        return 0;
    } else {
        return n + Sum(n - 1);
    }
}

/*
A function that recursively finds the largest value in an array.
It compares the last element of the array with the largest value
from the rest of the array and returns the larger one
*/
int Largest(const int array[], int size) {
    if (size == 1) {                                // If the array has only one element, return it
        return array[0];
    } else if (array[size - 1] > Largest(array, size - 1)) { 
        
        return array[size - 1];                     // Compare the last element with the largest value from the rest of the array
    } else {
        return Largest(array, size - 1);            // Return the largest value from the rest of the array
    }
}

/*
A function that iterates through a 2D grid to find and count "eagles."
An eagle is a connected group of non-zero cells. The function uses
FindEagles to determine the size of each eagle and increments the count
*/
void FindEagle(vector<vector<int>>&grid, int rows, int cols) {
    int numEagles = 0;                                                  // Counter for the number of eagles found

    for (int i = 0; i < rows; i++) {                                    // Iterate through each cell in the grid
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != 0) {                                      // If the cell is non-zero, it is part of an eagle
                int size = FindEagles(grid, i, j);                      // Find the size of the eagle
                cout << "An eagle size " << size << " is found.\n";
                numEagles++;                                            // Increment the eagle count
            }
        }
    }
    cout << "\n" << numEagles << " eagle(s) found in the picture.\n";         // Display the number of eagles found
}

/*
A recursive function that calculates the size of an eagle in a 2D grid.
An eagle is a connected group of non-zero cells. The function marks visited
cells as 0 to avoid counting them multiple times
*/
int FindEagles(vector<vector<int>>&grid, int x, int y) {
    // Error cheching to make sure grid is within bounds
    if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] == 0) {
        return 0;
    }

    int size = 1;       // Start with size 1 for the current cell
    grid[x][y] = 0;     // Mark the current cell as visited by setting it to 0

    // Recursively check all 8 possible directions
    size += FindEagles(grid, x + 1, y);     // Down
    size += FindEagles(grid, x - 1, y);     // Up
    size += FindEagles(grid, x, y + 1);     // Right
    size += FindEagles(grid, x, y - 1);     // Left
    size += FindEagles(grid, x + 1, y + 1); // Down-Right
    size += FindEagles(grid, x - 1, y + 1); // Up-Right
    size += FindEagles(grid, x + 1, y - 1); // Down-Left
    size += FindEagles(grid, x - 1, y - 1); // Up-Left

    return size;                            // Return the total size of the eagle
}