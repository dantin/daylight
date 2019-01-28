#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    int i;

    if (size < 1) {
        printf("[]\n");
        return;
    }

    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

int max_sub_array(int *nums, int nums_size)
{
    int i, total = 0, max = INT_MIN;

    for (i = 0; i < nums_size; i++) {
        total += nums[i];
        max = total > max ? total : max;
        if (total < 0) {
            total = 0;
        }
    }

    return max;
}

int main(int argc, char **argv)
{
    int nums1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4}, len1 = sizeof(nums1) / sizeof(int);
    struct object inputs[] = {
        {.nums = nums1, .len = len1},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        printf("\n Input: "); print_nums(nums, size);
        int max = max_sub_array(nums, size);
        printf(" Output: %d\n", max);
    }

    return EXIT_SUCCESS;
}
