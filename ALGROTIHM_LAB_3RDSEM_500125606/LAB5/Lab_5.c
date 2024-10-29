#include <stdio.h>
#include <limits.h>
#include <time.h>

// Function to print the optimal parenthesis placement
void printOptimalParenthesis(int i, int j, int n, int *bracket, char *name) {
    if (i == j) {
        printf("%c", (*name)++);
        return;
    }
    printf("(");

    // Recursively print the left and right subsets
    printOptimalParenthesis(i, *((bracket + i * n) + j), n, bracket, name);
    printOptimalParenthesis(*((bracket + i * n) + j) + 1, j, n, bracket, name);

    printf(")");
}

// Matrix Chain Multiplication function using DP with detailed cost printing
int MatrixChainOrder(int p[], int n) {
    int m[n][n];       // Minimum number of multiplications table
    int bracket[n][n]; // Stores optimal split point for printing order

    // Initialize main diagonal to zero
    for (int i = 1; i < n; i++)
        m[i][i] = 0;

    // L is the chain length
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            printf("Calculating cost for matrices from A%d to A%d\n", i, j);
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                printf("Split at A%d: Cost = %d\n", k, q);
                if (q < m[i][j]) {
                    m[i][j] = q;
                    bracket[i][j] = k; // Store split point in bracket
                }
            }
            printf("Minimum cost for multiplying A%d to A%d is %d\n\n", i, j, m[i][j]);
        }
    }

    // Display optimal order of multiplication
    char name = 'A';
    printf("Optimal Parenthesization is: ");
    printOptimalParenthesis(1, n - 1, n, (int *)bracket, &name);
    printf("\n");

    return m[1][n - 1]; // Return minimum cost of multiplication
}

int main() {
    int arr[] = {1, 2, 3, 4}; // Dimensions of matrices A1 (1x2), A2 (2x3), A3 (3x4)
    int size = sizeof(arr) / sizeof(arr[0]);

    clock_t start = clock();
    int min_cost = MatrixChainOrder(arr, size);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Minimum number of multiplications is %d\n", min_cost);
    printf("Time taken to compute optimal parenthesization: %f seconds\n", time_taken);

    return 0;
}
