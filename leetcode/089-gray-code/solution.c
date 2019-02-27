#include <stdio.h>
#include <stdlib.h>

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }

    int i;
    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
}

int *gray_code(int n, int *return_size)
{
    if (n < 0) {
        return NULL;
    }

    int i, count = 1 << n;
    int *codes = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        codes[i] = (i >> 1) ^ i;
    }

    *return_size = count;
    return codes;
}

int main(int argc, char **argv)
{
    int inputs[] = { 2, 0 };
    int i, return_size, len = sizeof(inputs) / sizeof(int);

    for (i = 0; i < len; i++) {
        int n = inputs[i];

        printf("\n Input: %d\n", n);
        int *codes = gray_code(n, &return_size);
        printf(" Output: ");
        print_nums(codes, return_size);
        printf("\n");
        free(codes);
    }

    return EXIT_SUCCESS;
}
