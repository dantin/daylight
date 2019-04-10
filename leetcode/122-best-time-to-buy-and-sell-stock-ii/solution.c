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
    int i, total = 0;
    for (i = 1; i < prices_size; i++) {
        total += prices[i] > prices[i - 1] ? prices[i] - prices[i - 1] : 0;
    }
    return total;
}

int main(int argc, char **argv)
{
    int nums1[] = { 7, 1, 5, 3, 6, 4 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 1, 2, 3, 4, 5 }, len2 = sizeof(nums2) / sizeof(int);
    int nums3[] = { 7, 6, 4, 3, 1 }, len3 = sizeof(nums3) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
        { .nums = nums3, .len = len3 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Input: ");
        print_nums(nums, size);

        int total = max_profit(nums, size);
        printf(" Output: %d\n", total);
    }

    return EXIT_SUCCESS;
}
