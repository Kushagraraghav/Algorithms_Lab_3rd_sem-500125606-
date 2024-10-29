#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int weight;
    int value;
    double ratio; // value-to-weight ratio
} Item;

// Function to compare items by their ratio
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    return (itemB->ratio < itemA->ratio) - (itemB->ratio > itemA->ratio);
}

// Greedy approach to 0/1 Knapsack
double greedy_knapsack(Item items[], int n, int capacity) {
    qsort(items, n, sizeof(Item), compare); // Sort items by ratio
    double totalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].value * ((double)capacity / items[i].weight);
            break; // The knapsack is full
        }
    }
    return totalValue;
}

// Dynamic programming approach to 0/1 Knapsack
int dynamic_knapsack(Item items[], int n, int capacity) {
    int dp[n + 1][capacity + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0; // Base case
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = (items[i - 1].value + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w])
                               ? items[i - 1].value + dp[i - 1][w - items[i - 1].weight]
                               : dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w]; // Item can't be included
            }
        }
    }
    return dp[n][capacity];
}

int main() {
    int capacity = 50; // Maximum capacity of the knapsack
    Item items[] = {
        {10, 60, 0}, // weight, value
        {20, 100, 0},
        {30, 120, 0}
    };
    int n = sizeof(items) / sizeof(items[0]);

    // Calculate value-to-weight ratio for greedy approach
    for (int i = 0; i < n; i++) {
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    // Measure time for Greedy approach
    clock_t start_time = clock();
    double greedy_result = greedy_knapsack(items, n, capacity);
    clock_t end_time = clock();
    double greedy_time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Greedy Knapsack Result: %.2f\n", greedy_result);
    printf("Time taken for Greedy approach: %.6f seconds\n", greedy_time_taken);

    // Measure time for Dynamic Programming approach
    start_time = clock();
    int dp_result = dynamic_knapsack(items, n, capacity);
    end_time = clock();
    double dp_time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Dynamic Programming Knapsack Result: %d\n", dp_result);
    printf("Time taken for Dynamic Programming approach: %.6f seconds\n", dp_time_taken);

    return 0;
}



