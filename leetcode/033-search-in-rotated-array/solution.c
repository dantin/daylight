#include <stdio.h>
#include <stdlib.h>

struct object {
    int *nums;
    int len;
    int target;
};

void print_nums(int *nums, int size)
{
    int i;

    if (size <= 0) {
        return;
    }

    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

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
    return nums[high] == target ? high : -1;
}

int find_pivot(int *nums, int size)
{
    int low = 0;
    int high = size - 1;
    while (low < high && nums[low] > nums[high]) {
        int mid = low + (high - low) / 2;
        if (nums[mid] > nums[high]) {
            low = mid + 1;
        } else if (nums[mid] < nums[low]) {
            high = mid;
        }
    }
    return low;
}

int search(int *nums, int nums_size, int target)
{
    if (nums_size <= 0) {
        return -1;
    }
    if (nums_size == 1) {
        return target == nums[0] ? 0 : -1;
    }

    int pivot = find_pivot(nums, nums_size);
    if (pivot == 0) {
        return binary_search(nums, nums_size, target);
    } else if (target >= nums[0]) {
        return binary_search(nums, pivot, target);
    } else if (target <= nums[nums_size - 1]) {
        int idx = binary_search(nums + pivot, nums_size - pivot, target);
        return idx >= 0 ? idx + pivot : -1;
    }
    return -1;
}

int main(int argc, char **argv)
{
    int nums1[] = {4, 5, 6, 7, 0, 1, 2}, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {4, 5, 6, 7, 0, 1, 2}, len2 = sizeof(nums2) / sizeof(int);
    int nums3[] = {4, 5, 6, 7, 0, 1, 2}, len3 = sizeof(nums2) / sizeof(int);
    struct object inputs[] = {
        {.nums = nums1, .len = len1, .target = 0},
        {.nums = nums2, .len = len2, .target = 3},
        {.nums = nums3, .len = len3, .target = 1},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size= inputs[i].len;
        int target = inputs[i].target;
        printf("\n nums = "); print_nums(nums, size);
        printf(" target = %d\n", target);
        int o = search(nums, size, target);
        printf(" Output = %d\n", o);
    }

    return EXIT_SUCCESS;
}
