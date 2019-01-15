#include <stdio.h>
#include <stdlib.h>

struct object {
    int *nums;
    int len;
    int target;
};

void print_nums(int *nums, int size)
{
    if (size <= 0) {
        return;
    }

    int i;
    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    putchar(']');
}

int search_insert(int *nums, int nums_size, int target)
{
    int low = -1, high = nums_size;

    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (target > nums[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return high;
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 3, 5, 6}, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {1, 3, 5, 6}, len2 = sizeof(nums2) / sizeof(int);
    int nums3[] = {1, 3, 5, 6}, len3 = sizeof(nums3) / sizeof(int);
    int nums4[] = {1, 3, 5, 6}, len4 = sizeof(nums4) / sizeof(int);
    struct object inputs[] = {
        {.nums = nums1, .len = len1, .target = 5},
        {.nums = nums2, .len = len2, .target = 2},
        {.nums = nums3, .len = len3, .target = 7},
        {.nums = nums4, .len = len4, .target = 0},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        int target = inputs[i].target;
        printf("\n Input: "); print_nums(nums, size); printf(", %d\n", target);
        int pos = search_insert(nums, size, target);
        printf(" Output: %d\n", pos);
    }

    return EXIT_SUCCESS;
}
