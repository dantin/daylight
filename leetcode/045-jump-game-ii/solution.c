#include <stdio.h>
#include <stdlib.h>

struct object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    int i;
    if (size < 1) {
        printf("[]\n");
    }

    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

inline int max(int lhs, int rhs)
{
    return lhs > rhs ? lhs : rhs;
}

int jump(int *nums, int nums_size)
{
    int i, low = 0, high = 0;
    int steps = 0;

    while (high < nums_size - 1) {
        int right = 0;
        for (i = low; i <= high; i++) {
            right = max(i + nums[i], right);
        }
        low = high + 1;
        high = right;
        steps++;
    }

    return steps;
}

int main(int argc, char **argv)
{
    int nums1[] = {2, 3, 1, 1, 4}, len1 = sizeof(nums1) / sizeof(int);
    struct object inputs[] = {
        {.nums = nums1, .len = len1},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        printf("\n Input: "); print_nums(nums, size);
        int steps = jump(nums, size);
        printf(" Output: %d\n", steps);
    }
    
    return EXIT_SUCCESS;
}
