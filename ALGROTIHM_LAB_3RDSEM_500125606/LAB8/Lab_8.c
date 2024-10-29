#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void print_subset(int nums[], int n, int target, bool dp[n + 1][target + 1]) {
    int i = n, j = target;
    printf("Subset: ");
    
    while (i > 0 && j > 0) {
        // If this item is included in the subset
        if (dp[i][j] && !dp[i - 1][j]) {
            printf("%d ", nums[i - 1]);
            j -= nums[i - 1];
        }
        i--;
    }
    printf("\n");
}

bool subset_sum(int nums[], int n, int target) {
    // Create a 2D array to store results of subproblems
    bool dp[n + 1][target + 1];

    // If the target is 0, then the answer is true (empty set)
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    // Fill the subset sum table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (nums[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Print the subset if the target sum is possible
    if (dp[n][target]) {
        print_subset(nums, n, target, dp);
    }

    return dp[n][target];
}

int main() {
    int nums[] = {3, 34, 4, 12, 5, 2};
    int target = 9;
    int n = sizeof(nums) / sizeof(nums[0]);

    // Measure execution time
    clock_t start_time = clock();
    bool result = subset_sum(nums, n, target);
    clock_t end_time = clock();

    if (result) {
        printf("Subset with given sum exists.\n");
    } else {
        printf("Subset with given sum does not exist.\n");
    }

    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken: %.6f seconds\n", time_taken);

    return 0;
}



