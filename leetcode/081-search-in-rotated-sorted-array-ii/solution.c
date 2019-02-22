#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>

struct Object {
    int *nums;
    int len;
    int target;
};

int binary_search(int *nums, int size, int target)
{
    int low = -1;
    int high = size;
    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (target > nums[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }

    if (high == size || nums[high] != target) {
        return -1;
    } else {
        return high;
    }
}

bool search(int *nums, int nums_size, int target)
{
    if (nums_size < 1) {
        return false;
    }

    if (nums_size == 1) {
        return nums[0] == target;
    }

    int i;
    for (i = 1; i < nums_size; i++) {
        if (nums[i] < nums[i - 1]) {
            break;
        }
    }

    if (i == 0) {
        return binary_search(nums, nums_size, target) >= 0;
    } else if (target >= nums[0]) {
        return binary_search(nums, i, target) >= 0;
    } else if (target <= nums[nums_size - 1]) {
        return binary_search(nums + i, nums_size - i, target) >= 0;
    }
    return false;
}

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

int main(int argc, char **argv)
{
    int nums1[] = {2, 5, 6, 0, 0, 1, 2}, len1 = sizeof(nums1) / sizeof(int), target1 = 0;
    int nums2[] = {2, 5, 6, 0, 0, 1, 2}, len2 = sizeof(nums2) / sizeof(int), target2 = 3;
    struct Object inputs[] = {
        { .nums = nums1, .len = len1, .target = target1 },
        { .nums = nums2, .len = len2, .target = target2 },
    };
    int i, len = sizeof(inputs) /sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        int target = inputs[i].target;

        printf("\n Inputs: nums = ");
        print_nums(nums, size);
        printf(", target = %d\n", target);

        bool found = search(nums, size, target);

        printf(" Output: %s\n", found ? "true" : "false");
    }

    return EXIT_SUCCESS;
}
