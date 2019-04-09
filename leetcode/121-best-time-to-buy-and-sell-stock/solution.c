#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]\n");
        return;
    }
    int i;
    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

int max_profit(int *prices, int prices_size)
{
    if (prices_size < 1) {
        return 0;
    }

    int i, diff = 0, min = prices[0];
    for (i = 1; i < prices_size; i++) {
        if (prices[i] < min) {
            min = prices[i];
        } else {
            diff = prices[i] - min > diff ? prices[i] - min : diff;
        }
    }

    return diff;
}

int main(int argc, char **argv)
{
    int nums1[] = { 7, 1, 5, 3, 6, 4 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 7, 6, 4, 3, 1 },    len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Input: ");
        print_nums(nums, size);

        int profit = max_profit(nums, size);
        printf(" Output: %d\n", profit);
    }

    return EXIT_SUCCESS;
}
