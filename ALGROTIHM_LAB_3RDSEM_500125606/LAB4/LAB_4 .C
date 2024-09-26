// 4. Implement the activity selection problem to get a clear understanding of greedy approach.

#include <stdio.h>

// Function to print the maximum number of activities that can be done
void activitySelection(int start[], int end[], int n) {
    int i, j;

    printf("Selected activities are:\n");

    // The first activity is always selected
    i = 0;
    printf("Activity %d (Start: %d, End: %d)\n", i+1, start[i], end[i]);

    // Consider rest of the activities
    for (j = 1; j < n; j++) {
        // If this activity has a start time greater than or equal to the
        // end time of the previously selected activity, select it
        if (start[j] >= end[i]) {
            printf("Activity %d (Start: %d, End: %d)\n", j+1, start[j], end[j]);
            i = j;  // Update i to the current activity
        }
    }
}

int main() {
    // Example set of activities with their start and end times
    int start[] = {1, 3, 0, 5, 8, 5};
    int end[] = {2, 4, 6, 7, 9, 9};
    int n = sizeof(start) / sizeof(start[0]);

    activitySelection(start, end, n);

    return 0;
}
