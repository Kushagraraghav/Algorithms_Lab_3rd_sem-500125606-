#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int weight;
    int value;
} Item;

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Dynamic Programming Approach
int knapsack_dp(Item items[], int n, int capacity) {
    int dp[n + 1][capacity + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0; // Base case
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w]; // Item can't be included
            }
        }
    }
    return dp[n][capacity];
}

// Backtracking Approach
int knapsack_backtracking(Item items[], int n, int capacity, int index, int currentValue) {
    if (index >= n || capacity <= 0) {
        return currentValue;
    }

    // Don't include the current item
    int maxValue = knapsack_backtracking(items, n, capacity, index + 1, currentValue);

    // Include the current item, if it fits
    if (items[index].weight <= capacity) {
        maxValue = max(maxValue, knapsack_backtracking(items, n, capacity - items[index].weight, index + 1, currentValue + items[index].value));
    }

    return maxValue;
}

// Branch & Bound Approach
typedef struct {
    int level;        // Current level in the decision tree
    int profit;       // Profit at this node
    int bound;        // Upper bound of profit
    int weight;       // Weight at this node
} Node;

int bound(Node u, int n, int capacity, Item items[]) {
    if (u.weight >= capacity) return 0; // Can't include this node
    int profitBound = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;

    // Greedily add items to the profitBound
    while (j < n && totalWeight + items[j].weight <= capacity) {
        totalWeight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }

    // If there's room for the last item, add a fraction of it
    if (j < n) {
        profitBound += (capacity - totalWeight) * items[j].value / items[j].weight;
    }

    return profitBound;
}

int knapsack_branch_bound(Item items[], int n, int capacity) {
    Node u, v;
    int maxProfit = 0;
    // Sorting items by value/weight ratio
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((items[i].value / (double)items[i].weight) < (items[j].value / (double)items[j].weight)) {
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }

    // Queue for BFS
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = bound(u, n, capacity, items);

    // Use a simple array as a stack for backtracking
    Node stack[n]; // Stack for storing nodes
    int top = -1;
    stack[++top] = u;

    while (top >= 0) {
        u = stack[top--];

        // Move to next level
        v.level = u.level + 1;

        // If we include the next item
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;

        if (v.weight <= capacity && v.profit > maxProfit) {
            maxProfit = v.profit; // Update maxProfit
        }
        v.bound = bound(v, n, capacity, items);
        if (v.bound > maxProfit) {
            stack[++top] = v; // Add node to stack if its bound is greater
        }

        // Exclude the next item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, capacity, items);
        if (v.bound > maxProfit) {
            stack[++top] = v; // Add node to stack if its bound is greater
        }
    }

    return maxProfit;
}

int main() {
    Item items[] = {
        {10, 60}, // weight, value
        {20, 100},
        {30, 120}
    };
    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 50;

    // Measure execution time for Dynamic Programming
    clock_t start_time = clock();
    int dp_result = knapsack_dp(items, n, capacity);
    clock_t end_time = clock();
    printf("Dynamic Programming Result: %d\n", dp_result);
    printf("Time taken for Dynamic Programming: %.6f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    // Measure execution time for Backtracking
    start_time = clock();
    int backtrack_result = knapsack_backtracking(items, n, capacity, 0, 0);
    end_time = clock();
    printf("Backtracking Result: %d\n", backtrack_result);
    printf("Time taken for Backtracking: %.6f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    // Measure execution time for Branch & Bound
    start_time = clock();
    int bb_result = knapsack_branch_bound(items, n, capacity);
    end_time = clock();
    printf("Branch & Bound Result: %d\n", bb_result);
    printf("Time taken for Branch & Bound: %.6f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
