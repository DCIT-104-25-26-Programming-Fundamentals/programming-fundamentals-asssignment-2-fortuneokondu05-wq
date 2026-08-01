// =============================================================================
// PROGRAMMING FUNDAMENTALS — Assignment 4
// =============================================================================
//
// TASK: Matrix Operations
//
// Write a C++ program that performs three operations on matrices (2D arrays),
// each implemented in its own function.
//
// NOTE: Use a fixed maximum size of 10 for array dimensions.
//       Declare arrays as int matrix[10][10].
//
// -----------------------------------------------------------------------------
// PART A — Transpose a Matrix
// -----------------------------------------------------------------------------
// - Read an M x N matrix from the user.
// - Compute and display its transpose (rows become columns, columns become rows).
//
// Example (2 x 3 input):
//
//   Original Matrix:      Transposed Matrix:
//   1  2  3               1  4
//   4  5  6               2  5
//                         3  6
//
// -----------------------------------------------------------------------------
// PART B — Add Two Matrices
// -----------------------------------------------------------------------------
// - Read two matrices of exactly the same size (M x N).
// - Compute their element-wise sum and display the result.
//
// -----------------------------------------------------------------------------
// PART C — Multiply Two Matrices
// -----------------------------------------------------------------------------
// - Read matrix A of size M x N and matrix B of size N x P.
//   (Number of COLUMNS in A must equal number of ROWS in B.)
// - Compute and display the matrix product A x B (result is M x P).
//
// -----------------------------------------------------------------------------
// EXPECTED INPUT FORMAT
// -----------------------------------------------------------------------------
// The user enters each row's values one at a time:
//
//   Enter number of rows: 2
//   Enter number of columns: 3
//   Enter element [0][0]: 1
//   Enter element [0][1]: 2
//   ...
//
// -----------------------------------------------------------------------------
// REQUIREMENTS
// -----------------------------------------------------------------------------
// - Use nested loops for all operations (no external libraries).
// - Each operation must be in its own function (see scaffold below).
// - Display each matrix in a neat, aligned grid using setw().
// - Tip: Complete Part A first, then Parts B and C.
//

// =============================================================================
// YOUR CODE BELOW — remove the // symbols from the scaffold and fill it in
// =============================================================================

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
void readMatrix(int matrix[10][10], int &rows, int &cols) {
    cout << "\nEnter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;
    
    cout << "\nEnter the matrix elements (row by row):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Enter element [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
}

void displayMatrix(int matrix[10][10], int rows, int cols) {
    cout << "\nMatrix (" << rows << " x " << cols << "):\n";
    cout << string(cols * 6, '-') << "\n";  // Top border
    
    for (int i = 0; i < rows; i++) {
        cout << "| ";
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << matrix[i][j] << " ";
        }
        cout << "|\n";
    }
    cout << string(cols * 6, '-') << "\n";  // Bottom border
}

void transposeMatrix() {
    int matrix[10][10], transpose[10][10];
    int rows, cols;
    
    cout << "\n========== PART A: TRANSPOSE A MATRIX ==========\n";
    
    // Read the matrix
    readMatrix(matrix, rows, cols);
    displayMatrix(matrix, rows, cols);
    
    // THE TRICK: Swap rows and columns
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transpose[j][i] = matrix[i][j];  // Element at [i][j] → [j][i]
        }
    }
    
    displayMatrix(transpose, cols, rows);  // Note: cols, rows (swapped!)
}

void addMatrices() {
    int matrixA[10][10], matrixB[10][10], result[10][10];
    int rows, cols;
    
    // Read both matrices
    cout << "\n--- Read Matrix A ---";
    readMatrix(matrixA, rows, cols);
    
    cout << "\n--- Read Matrix B ---";
    int rowsB, colsB;
    readMatrix(matrixB, rowsB, colsB);
    
    // ERROR CHECK: Must have same dimensions
    if (rows != rowsB || cols != colsB) {
        cout << "\nERROR: Matrices must have the same dimensions!\n";
        return;
    }
    
    displayMatrix(matrixA, rows, cols);
    displayMatrix(matrixB, rows, cols);
    
    // ADD: element by element
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    
    displayMatrix(result, rows, cols);
}

void multiplyMatrices() {
    int matrixA[10][10], matrixB[10][10], result[10][10];
    int rowsA, colsA, rowsB, colsB;
    
    readMatrix(matrixA, rowsA, colsA);
    readMatrix(matrixB, rowsB, colsB);
    
    // ERROR CHECK: colsA must equal rowsB
    if (colsA != rowsB) {
        cout << "\nERROR: For A (M x N) * B (N x P):\n";
        cout << "Columns of A must equal rows of B\n";
        return;
    }
    
    displayMatrix(matrixA, rowsA, colsA);
    displayMatrix(matrixB, rowsB, colsB);
    
    // MULTIPLY using triple nested loop
    for (int i = 0; i < rowsA; i++) {              // rows of A
        for (int j = 0; j < colsB; j++) {          // columns of B
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {      // columns of A = rows of B
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    
    displayMatrix(result, rowsA, colsB);  // Result is rowsA x colsB
}

int main() {
    int choice;
    char continueChoice;
    
    do {
        cout << "\nChoose an operation:\n";
        cout << "1. Transpose a Matrix\n";
        cout << "2. Add Two Matrices\n";
        cout << "3. Multiply Two Matrices\n";
        cout << "4. Exit\n";
        
        cin >> choice;
        
        switch (choice) {
            case 1:
                transposeMatrix();
                break;
            case 2:
                addMatrices();
                break;
            case 3:
                multiplyMatrices();
                break;
            case 4:
                return 0;
            default:
                cout << "\nInvalid choice!\n";
        }
        
        cout << "\nDo another operation? (y/n): ";
        cin >> continueChoice;
        
    } while (continueChoice == 'y' || continueChoice == 'Y');
    
    return 0;
}
