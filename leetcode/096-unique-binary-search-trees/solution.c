#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * f(n) = f(0)f(n-1) + f(1)f(n-2) + ... + f(n-2)f(1) + f(n-1)f(0)
 */
int num_trees(int n)
{
    int i, j;
    int *dp = malloc((n + 1) * sizeof(int));
    memset(dp, 0, (n + 1) * sizeof(int));
    dp[0] = 1;
    for (i = 1; i <= n; i++) {
        for (j = 0; j < i; j++) {
            dp[i] += dp[j] * dp[i - j - 1];
        }
    }
    int cnt = dp[n];
    free(dp);
    return cnt;
}

int main(int argc, char **argv)
{
    int inputs[] = { 1, 2, 3 }, len = sizeof(inputs) / sizeof(int);
    int i;

    for (i = 0; i < len; i++) {
        int n = inputs[i];

        printf("\n Input: %d\n", n);
        int cnt = num_trees(n);
        printf(" Output: %d\n", cnt);
    }

    return EXIT_SUCCESS;
}
