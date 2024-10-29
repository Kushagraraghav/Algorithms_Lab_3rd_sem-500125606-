#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define d 256 // Number of characters in the input alphabet

// Naive String Matching Algorithm
void naive_search(char* txt, char* pat) {
    int M = strlen(pat);
    int N = strlen(txt);
    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++) {
            if (txt[i + j] != pat[j]) break;
        }
        if (j == M) {
            printf("Naive: Pattern found at index %d\n", i);
        }
    }
}

// Rabin-Karp Algorithm
void rabin_karp(char* txt, char* pat, int q) {
    int M = strlen(pat);
    int N = strlen(txt);
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;

    for (int i = 0; i < M - 1; i++) {
        h = (h * d) % q; // The value of h would be "d^(M-1)%q"
    }

    // Calculate the hash value of pattern and first window of text
    for (int i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (int i = 0; i <= N - M; i++) {
        if (p == t) { // Check for match
            int j;
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) break;
            }
            if (j == M) {
                printf("Rabin-Karp: Pattern found at index %d\n", i);
            }
        }

        // Calculate hash value for next window of text
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0) t += q; // We might get negative value of t
        }
    }
}

// KMP Algorithm
void KMPSearch(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M]; // Longest Prefix Suffix

    // Preprocess the pattern to create the LPS array
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0
    int i = 1;

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0; // Index for txt[]
    int j = 0; // Index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            i++;
            j++;
        }

        if (j == M) {
            printf("KMP: Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    char txt[] = "ABABDABACDABABCABAB";
    char pat[] = "ABAB";
    int q = 101; // A prime number for hashing

    // Measure execution time for Naive Search
    clock_t start, end;

    start = clock();
    naive_search(txt, pat);
    end = clock();
    double naive_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Naive Search Execution Time: %.6f seconds\n", naive_time);

    // Measure execution time for Rabin-Karp
    start = clock();
    rabin_karp(txt, pat, q);
    end = clock();
    double rabin_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Rabin-Karp Execution Time: %.6f seconds\n", rabin_time);

    // Measure execution time for KMP
    start = clock();
    KMPSearch(pat, txt);
    end = clock();
    double kmp_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("KMP Execution Time: %.6f seconds\n", kmp_time);

    return 0;
}

