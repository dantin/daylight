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
    printf("]\n");
}

int binary_search_start(int *nums, int size, int target)
{
    int low = -1, high = size;

    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (target > nums[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return (high != size && nums[high] == target) ? high : -1;
}

int binary_search_end(int *nums, int size, int target)
{
    int low = -1, high = size;

    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (target < nums[mid]) {
            high = mid;
        } else {
            low = mid;
        }
    }

    return (low != -1 && nums[low] == target) ? low : -1;
}

int *search_range(int *nums, int nums_size, int target, int *return_size)
{
    int *range = malloc(2 * sizeof(int));
    *return_size = 2;

    if (nums_size == 0) {
        range[0] = range[1] = -1;
    } else {
        range[0] = binary_search_start(nums, nums_size, target);
        range[1] = binary_search_end(nums, nums_size, target);
    }
    return range;
}

int main(int argc, char **argv)
{
    int nums1[] = {5, 7, 7, 8, 8, 10}, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {5, 7, 7, 8, 8, 10}, len2 = sizeof(nums2) / sizeof(int);
    struct object inputs[] = {
        {.nums = nums1, .len = len1, .target = 8},
        {.nums = nums2, .len = len2, .target = 6},
    };
    int i, range_size, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        int target = inputs[i].target;
        printf("\n nums = "); print_nums(nums, size);
        printf(" target = %d\n", target);
        int *range = search_range(nums, size, target, &range_size);
        printf(" Output: "); print_nums(range, range_size);
    }

    return EXIT_SUCCESS;
}
