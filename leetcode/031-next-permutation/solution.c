#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

void print_nums(int *nums, int size)
{
    int i;

    if (size <= 0) {
        printf("[]\n");
        return;
    }
    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
}

void reverse(int *nums, int size)
{
    int left = 0;
    int right = size - 1;
    while (left < right) {
        int tmp = nums[left];
        nums[left] = nums[right];
        nums[right] = tmp;
        left++;
        right--;
    }
}

/**
 * e.g.    6   8   7   4   3   2
 * step1  (6)  8   7   4   3   2
 * step2   6   8  (7)  4   3   2
 * step3  (7)  8  (6)  4   3   2
 * step4   7  [8   6   4   3   2]
 *         7  [2   3   4   6   8]
 *
 * Explain:
 *
 *  1. from right to left, find the `Partition Number` which violate the increate trend,
 *     in this example, 6 will be selected.
 *  2. from right to left, find the `Change Number` which large than Partition Number.
 *     Here 7 will be selected.
 *  3. Swap the Partition Number and Change Number.
 *  4. Reverse all digits on the right of Partition Number.
 */
void next_permutation(int *nums, int nums_size)
{
    if (nums_size <= 1) {
        return;
    }

    int *p = nums + nums_size - 1;
    int *q = p;

    // find the 1st peek backward.
    while (p != nums && *(p - 1) >= *p) {
        p--;
    }

    if (p != nums) {
        int n = *(p - 1);
        while (*q <= n) {
            q--;
        }

        int tmp = *q;
        *q = *(p - 1);
        *(p - 1) = tmp;
    }
    reverse(p, nums_size - (p - nums));
}

int main(int argc, char **argv)
{
    int inputs[][SIZE] = {
        {1, 2, 3},
        {3, 2, 1},
        {1, 1, 5},
        {1, 6, 5},
    };
    int i, *nums, len = sizeof(inputs) / sizeof(int[SIZE]);

    for (i = 0; i < len; i++) {
        nums = inputs[i];
        printf("\n "); print_nums(nums, SIZE);
        printf(" -> ");
        next_permutation(nums, SIZE);
        print_nums(nums, SIZE);
        putchar('\n');
    }

    return EXIT_SUCCESS;
}
