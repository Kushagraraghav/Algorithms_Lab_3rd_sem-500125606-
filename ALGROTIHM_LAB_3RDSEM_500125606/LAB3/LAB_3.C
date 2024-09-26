//3. Compare the performance of Strassen method of matrix multiplication with traditional way of matrix multiplication.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate memory for a matrix
int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to free memory of a matrix
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to add two matrices
void addMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subtractMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Traditional matrix multiplication
void traditionalMultiply(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Strassen's matrix multiplication
void strassenMultiply(int** A, int** B, int** C, int n) {
    if (n <= 64) {  // Base case: use traditional method for small matrices
        traditionalMultiply(A, B, C, n);
        return;
    }

    int newSize = n / 2;

    int** A11 = allocateMatrix(newSize);
    int** A12 = allocateMatrix(newSize);
    int** A21 = allocateMatrix(newSize);
    int** A22 = allocateMatrix(newSize);
    int** B11 = allocateMatrix(newSize);
    int** B12 = allocateMatrix(newSize);
    int** B21 = allocateMatrix(newSize);
    int** B22 = allocateMatrix(newSize);

    int** P1 = allocateMatrix(newSize);
    int** P2 = allocateMatrix(newSize);
    int** P3 = allocateMatrix(newSize);
    int** P4 = allocateMatrix(newSize);
    int** P5 = allocateMatrix(newSize);
    int** P6 = allocateMatrix(newSize);
    int** P7 = allocateMatrix(newSize);

    int** C11 = allocateMatrix(newSize);
    int** C12 = allocateMatrix(newSize);
    int** C21 = allocateMatrix(newSize);
    int** C22 = allocateMatrix(newSize);

    int** tempA = allocateMatrix(newSize);
    int** tempB = allocateMatrix(newSize);

    // Dividing matrices into 4 sub-matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculate P1 to P7
    addMatrix(A11, A22, tempA, newSize);
    addMatrix(B11, B22, tempB, newSize);
    strassenMultiply(tempA, tempB, P1, newSize);  // P1 = (A11 + A22) * (B11 + B22)

    addMatrix(A21, A22, tempA, newSize);
    strassenMultiply(tempA, B11, P2, newSize);  // P2 = (A21 + A22) * B11

    subtractMatrix(B12, B22, tempB, newSize);
    strassenMultiply(A11, tempB, P3, newSize);  // P3 = A11 * (B12 - B22)

    subtractMatrix(B21, B11, tempB, newSize);
    strassenMultiply(A22, tempB, P4, newSize);  // P4 = A22 * (B21 - B11)

    addMatrix(A11, A12, tempA, newSize);
    strassenMultiply(tempA, B22, P5, newSize);  // P5 = (A11 + A12) * B22

    subtractMatrix(A21, A11, tempA, newSize);
    addMatrix(B11, B12, tempB, newSize);
    strassenMultiply(tempA, tempB, P6, newSize);  // P6 = (A21 - A11) * (B11 + B12)

    subtractMatrix(A12, A22, tempA, newSize);
    addMatrix(B21, B22, tempB, newSize);
    strassenMultiply(tempA, tempB, P7, newSize);  // P7 = (A12 - A22) * (B21 + B22)

    // Calculate C11, C12, C21, C22
    addMatrix(P1, P4, tempA, newSize);
    subtractMatrix(tempA, P5, tempB, newSize);
    addMatrix(tempB, P7, C11, newSize);  // C11 = P1 + P4 - P5 + P7

    addMatrix(P3, P5, C12, newSize);  // C12 = P3 + P5

    addMatrix(P2, P4, C21, newSize);  // C21 = P2 + P4

    addMatrix(P1, P3, tempA, newSize);
    subtractMatrix(tempA, P2, tempB, newSize);
    addMatrix(tempB, P6, C22, newSize);  // C22 = P1 + P3 - P2 + P6

    // Grouping into C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free allocated memory
    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(P1, newSize); freeMatrix(P2, newSize);
    freeMatrix(P3, newSize); freeMatrix(P4, newSize);
    freeMatrix(P5, newSize); freeMatrix(P6, newSize);
    freeMatrix(P7, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
    freeMatrix(tempA, newSize); freeMatrix(tempB, newSize);
}

// Function to measure execution time
double measureExecutionTime(void (*multiplyFunc)(int**, int**, int**, int), int** A, int** B, int** C, int n) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    multiplyFunc(A, B, C, n);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

int main() {
    srand(time(NULL));

    int sizes[] = {64, 128, 256, 512, 1024, 2048};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Matrix Size\tTraditional Time\tStrassen Time\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];

        int** A = allocateMatrix(n);
        int** B = allocateMatrix(n);
        int** C = allocateMatrix(n);

        // Initialize matrices A and B with random values
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                A[j][k] = rand() % 10;
                B[j][k] = rand() % 10;
            }
        }

        double traditionalTime = measureExecutionTime(traditionalMultiply, A, B, C, n);
        double strassenTime = measureExecutionTime(strassenMultiply, A, B, C, n);

        printf("%d x %d\t%.6f\t\t%.6f\n", n, n, traditionalTime, strassenTime);

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);
    }

    return 0;
}