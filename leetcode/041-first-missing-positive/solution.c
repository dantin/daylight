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
        printf("[]");
    }

    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    putchar(']');
}

inline void swap(int *lhs, int *rhs)
{
    int tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp;
}

int first_missing_positive(int *nums, int nums_size)
{
    if (nums_size < 1) {
        return 1;
    }

    int i = 0;
    while (i < nums_size) {
        if (nums[i] != i + 1 && nums[i] > 0 && nums[i] <= nums_size && nums[i] != nums[nums[i] - 1]) {
            swap(nums + i, nums + nums[i] - 1);
        } else {
            i++;
        }
    }

    for (i = 0; i < nums_size; i++) {
        if (nums[i] != i + 1) break;
    }

    return i + 1;
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 2, 0},         len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {3, 4, -1, 1},     len2 = sizeof(nums2) / sizeof(int);
    int nums3[] = {7, 8, 9, 11, 12}, len3 = sizeof(nums3) / sizeof(int);
    struct object inputs[] = {
        {.nums = nums1, .len = len1},
        {.nums = nums2, .len = len2},
        {.nums = nums3, .len = len3},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Input: "); print_nums(nums, size); putchar('\n');

        int miss = first_missing_positive(nums, size);
        printf(" Output: %d\n", miss);
    }

    return EXIT_SUCCESS;
}
