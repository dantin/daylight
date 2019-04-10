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
    if (prices_size <= 1) {
        return 0;
    }

    int i, tmp, diff = 0, min = prices[0];
    int *left_profit = malloc(prices_size * sizeof(int));
    for (i = 1; i < prices_size; i++) {
        if (prices[i] < min) {
            min = prices[i];
        } else {
            tmp = prices[i] - min;
            diff = tmp > diff ? tmp : diff;
        }
        left_profit[i] = diff;
    }

    int right_profit = 0;
    int max = prices[prices_size - 1];
    int total = left_profit[prices_size - 1];
    for (i = prices_size - 2; i >= 0; i--) {
        if (prices[i] > max) {
            max = prices[i];
        } else {
            tmp = max - prices[i];
            right_profit = tmp > right_profit ? tmp : right_profit;
        }
        tmp = left_profit[i] + right_profit;
        total = tmp > total ? tmp : total;
    }
    free(left_profit);

    return total;
}

int main(int argc, char **argv)
{
    int nums1[] = { 3, 3, 5, 0, 0, 3, 1, 4 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 1, 2, 3, 4, 5 }, len2 = sizeof(nums2) / sizeof(int);
    int nums3[] = { 7, 6, 4, 3, 1 }, len3 = sizeof(nums3) / sizeof(int);
    int nums4[] = { 1 }, len4 = sizeof(nums4) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
        { .nums = nums3, .len = len3 },
        { .nums = nums4, .len = len4 },
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
