#include <stdio.h>
#include <stdlib.h>

struct Object {
    int m;
    int n;
};

int unique_paths(int m, int n)
{
    int row, col, count;

    int *dp = malloc(m * n * sizeof(int));
    for (col = 0; col < m; col++) {
        dp[col] = 1;
    }
    for (row = 0; row < n; row++) {
        dp[row * m] = 1;
    }
    for (row = 1; row < n; row++) {
        for (col = 1; col < m; col++) {
            dp[row * m + col] = dp[row * m + col - 1] + dp[(row - 1) * m + col];
        }
    }
    count = dp[m * n - 1];
    free(dp);

    return count;
}

int main(int argc, char **argv)
{
    struct Object inputs[] = {
        {.m = 3, .n = 2},
        {.m = 7, .n = 3},
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int m = inputs[i].m;
        int n = inputs[i].n;
        printf("\n Input: m = %d, n = %d\n", m, n);
        int count = unique_paths(m, n);
        printf(" Output: %d\n", count);
    }

    return EXIT_SUCCESS;
}
