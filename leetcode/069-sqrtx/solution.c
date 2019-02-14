#include <stdio.h>
#include <stdlib.h>

int my_sqrt(int x)
{
    if (x == 0) {
        return 0;
    }

    unsigned int left = 1;
    unsigned int right = (unsigned int) x;
    while (1) {
        unsigned int mid = left + (right - left) / 2;
        if (mid > x / mid) {
            right = mid;
        } else {
            if (mid + 1 > x / (mid + 1)) {
                return mid;
            } else {
                left = mid;
            }
        }
    }
}

int main(int argc, char **argv)
{
    int inputs[] = { 4, 8 };
    int i, len = sizeof(inputs) / sizeof(int);

    for (i = 0; i < len; i++) {
        int x = inputs[i];
        printf("\n Input: %d\n", x);
        int root = my_sqrt(x);
        printf(" Output: %d\n", root);
    }

    return EXIT_SUCCESS;
}
