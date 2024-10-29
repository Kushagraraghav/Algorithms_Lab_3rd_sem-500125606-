#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define V 6 // Number of vertices in the graph

// Dijkstra's Algorithm
void dijkstra(int graph[V][V], int start) {
    int distances[V];
    bool visited[V];

    // Initialize distances and visited
    for (int i = 0; i < V; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }
    distances[start] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min_distance = INT_MAX, min_index;

        // Find the vertex with the minimum distance
        for (int v = 0; v < V; v++) {
            if (!visited[v] && distances[v] <= min_distance) {
                min_distance = distances[v];
                min_index = v;
            }
        }

        visited[min_index] = true;

        // Update distances of the adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[min_index][v] && distances[min_index] != INT_MAX &&
                distances[min_index] + graph[min_index][v] < distances[v]) {
                distances[v] = distances[min_index] + graph[min_index][v];
            }
        }
    }

    // Print the results
    printf("Dijkstra's Algorithm Result: ");
    for (int i = 0; i < V; i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");
}

// Bellman-Ford Algorithm
void bellman_ford(int graph[V][V], int start) {
    int distances[V];

    // Initialize distances
    for (int i = 0; i < V; i++) {
        distances[i] = INT_MAX;
    }
    distances[start] = 0;

    // Relax edges
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] && distances[u] != INT_MAX && distances[u] + graph[u][v] < distances[v]) {
                    distances[v] = distances[u] + graph[u][v];
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && distances[u] != INT_MAX && distances[u] + graph[u][v] < distances[v]) {
                printf("Graph contains a negative weight cycle\n");
                return;
            }
        }
    }

    // Print the results
    printf("Bellman-Ford Algorithm Result: ");
    for (int i = 0; i < V; i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");
}

int main() {
    // Example graph represented as an adjacency matrix
    int graph[V][V] = {
        {0, 7, 9, 0, 0, 14},
        {7, 0, 10, 15, 0, 0},
        {9, 10, 0, 11, 0, 2},
        {0, 15, 11, 0, 6, 0},
        {0, 0, 0, 6, 0, 9},
        {14, 0, 2, 0, 9, 0}
    };

    clock_t start, end;

    // Measuring Dijkstra's execution time
    start = clock();
    dijkstra(graph, 0);  // Start from vertex 0
    end = clock();
    double dijkstra_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Measuring Bellman-Ford execution time
    start = clock();
    bellman_ford(graph, 0);  // Start from vertex 0
    end = clock();
    double bellman_ford_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Display execution times
    printf("Dijkstra's Algorithm Time: %f seconds\n", dijkstra_time);
    printf("Bellman-Ford Algorithm Time: %f seconds\n", bellman_ford_time);

    return 0;
}
