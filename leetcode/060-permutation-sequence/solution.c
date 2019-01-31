#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
    int n;
    int k;
};

int factorial(int n)
{
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

char *get_permutation(int n, int k)
{
    int i;
    int *digits = malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        digits[i] = i + 1;
    }

    char *result = malloc(n + 1);
    for (i = 0; i < n; i++) {
        int fac = factorial(n - i - 1);
        int j = k > 1 ? (k - 1) / fac : 0;
        result[i] = digits[j] + '0';
        k -= j * fac;
        memmove(digits + j, digits + j + 1, (n - j) * sizeof(int));
    }
    result[n] = '\0';

    return result;
}

int main(int argc, char **argv)
{
    struct Object inputs[] = {
        { .n = 3, .k = 3 },
        { .n = 4, .k = 9 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int n = inputs[i].n;
        int k = inputs[i].k;
        printf("\n Input: n = %d, k = %d\n", n, k);
        char *permutation = get_permutation(n, k);
        printf(" %s\n", permutation);
    }

    return EXIT_SUCCESS;
}
