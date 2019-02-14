#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dfs(int n, int *count)
{
    if (n == 0) {
        return 0;
    } else if (count[n] > 0) {
        return count[n];
    } else {
        if (n >= 1) {
            count[n] += dfs(n - 1, count);
        }
        if (n >= 2) {
            count[n] += dfs(n - 2, count);
        }
        return count[n];
    }
}

int climb_stairs(int n)
{
    int *count = malloc((n + 1) * sizeof(int));
    memset(count, 0, (n + 1) * sizeof(int));
    count[1] = 1;
    if (n > 1) {
        count[2] = 2;
    }
    int stairs = dfs(n, count);
    free(count);
    return stairs;
}

int main(int argc, char **argv)
{
    int inputs[] = { 1, 2, 3 };
    int i, len = sizeof(inputs) / sizeof(int);

    for (i = 0; i < len; i++) {
        int n = inputs[i];
        printf("\n Input: %d\n", n);
        int x = climb_stairs(n);
        printf(" Output: %d\n", x);
    }

    return EXIT_SUCCESS;
}
