#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct object {
    int dividend;
    int divisor;
};

int divide(int dividend, int divisor)
{
    int sign = ((dividend ^ divisor) < 0) ? -1 : 1;
    unsigned int dvd = dividend > 0 ? dividend : -dividend;
    unsigned int dvs = divisor > 0 ? divisor : -divisor;
    unsigned int bit_num[33]; // bit_num store multiple of divisor.
    unsigned int i = 0;
    long long d = dvs;

    bit_num[i] = d;
    while (d <= dvd) {
        bit_num[++i] = d = d << 1;
    }
    i--;

    unsigned int result = 0;
    while (dvd >= dvs) {
        if (dvd >= bit_num[i]) {
            dvd -= bit_num[i];
            result += (1 << i);
        } else {
            i--;
        }
    }

    // check integer overflow or not.
    if (result > INT_MAX && sign > 0) {
        return INT_MAX;
    }

    return (int) result * sign;
}

int main(int argc, char **argv)
{
    struct object inputs[] = {
        {.dividend = 100, .divisor =  3},
        {.dividend = 10, .divisor = -3},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int dividend = inputs[i].dividend;
        int divisor = inputs[i].divisor;
        printf("\n dividend = %d, divisor = %d\n", dividend, divisor);
        int result = divide(dividend, divisor);
        printf(" Output: %d\n", result);
    }

    return EXIT_SUCCESS;
}
