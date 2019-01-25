#include <stdio.h>
#include <stdlib.h>

struct object {
    double x;
    int n;
};

double fast_pow(double x, int n)
{
    if (n == 0) { return 1.0; }
    if (n == 1) { return x; }
    double t = fast_pow(x, n / 2);
    return n & 1 ? t * t * x : t * t;
}

double my_pow(double x, int n)
{
    return n < 0 ? 1 / fast_pow(x, -n) : fast_pow(x, n);
}

int main(int argc, char **argv)
{
    struct object inputs[] = {
        {.x = 2.0, .n = 10},
        {.x = 2.1, .n = 3},
        {.x = 2.0, .n = -2},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        double x = inputs[i].x;
        int n = inputs[i].n;

        printf("\n Inputs: %f, %d\n", x, n);
        double p = my_pow(x, n);
        printf(" Output: %f\n", p);
    }

    return EXIT_SUCCESS;
}
