// 1. Implement the insertion inside iterative and recursive Binary search tree and compare their performance.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a BST node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Iterative BST insertion
struct Node* iterativeInsert(struct Node* root, int data) {
    struct Node* newNode = createNode(data);
    if (root == NULL) return newNode;

    struct Node* parent = NULL;
    struct Node* current = root;
    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else if (data > current->data)
            current = current->right;
        else
            return root; // No duplicates
    }

    if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Recursive BST insertion
struct Node* recursiveInsert(struct Node* root, int data) {
    if (root == NULL) return createNode(data);

    if (data < root->data)
        root->left = recursiveInsert(root->left, data);
    else if (data > root->data)
        root->right = recursiveInsert(root->right, data);

    return root;
}

// Utility function to print BST in-order (for verification)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Time comparison function for both insertions
void compareInsertionTimes(int arrays[5][10], int sizes[5]) {
    for (int i = 0; i < 5; i++) {
        printf("\n--- Array %d ---\n", i + 1);
        struct Node* root1 = NULL; // For iterative insertions
        struct Node* root2 = NULL; // For recursive insertions

        // Measure time for iterative insertion
        clock_t startIter = clock();
        for (int j = 0; j < sizes[i]; j++) {
            root1 = iterativeInsert(root1, arrays[i][j]);
        }
        clock_t endIter = clock();
        double timeIter = ((double)(endIter - startIter)) / CLOCKS_PER_SEC;

        // Measure time for recursive insertion
        clock_t startRecur = clock();
        for (int j = 0; j < sizes[i]; j++) {
            root2 = recursiveInsert(root2, arrays[i][j]);
        }
        clock_t endRecur = clock();
        double timeRecur = ((double)(endRecur - startRecur)) / CLOCKS_PER_SEC;

        printf("Iterative Insertion Time: %f seconds\n", timeIter);
        printf("Recursive Insertion Time: %f seconds\n", timeRecur);

        // Optional: Print BST (for verification)
        printf("In-order traversal (Iterative): ");
        inorderTraversal(root1);
        printf("\nIn-order traversal (Recursive): ");
        inorderTraversal(root2);
        printf("\n");
    }
}

// Driver function
int main() {
    // Define five sample arrays
    int arrays[5][10] = {
        {50, 30, 20, 40, 70, 60, 80},  // 7 elements
        {10, 20, 30, 40, 50, 60, 70, 80, 90}, // 9 elements
        {25, 15, 50, 10, 22, 35, 70, 40, 80}, // 9 elements
        {100, 90, 80, 70, 60}, // 5 elements
        {5, 25, 15, 35, 20, 30, 10}  // 7 elements
    };

    // Define the size of each array
    int sizes[5] = {7, 9, 9, 5, 7};

    // Compare insertion times
    compareInsertionTimes(arrays, sizes);

    return 0;
}
