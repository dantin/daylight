#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums1;
    int len1;
    int *nums2;
    int len2;
    int size1;
};

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

int binary_search(int *nums, int size, int target)
{
    int low = -1;
    int high = size;
    while (low + 1 < high) {
        int mid = high - (high - low) / 2;
        if (target > nums[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }

    if (high == size || nums[high] != target) {
        return -high - 1;
    } else {
        return high;
    }
}

void merge(int *nums1, int m, int *nums2, int n)
{
    int i, j, len1 = m;

    for (i = 0; i < n; i++) {
        // locate index in `nums1` for `num2[i]`.
        int index = binary_search(nums1, len1, nums2[i]);
        if (index < 0) {
            index = -index - 1;
        }
        // shift elements right from [index .. tail] to [index+1 .. tail].
        for (j = len1 - 1; j >= index; j--) {
            nums1[j + 1] = nums1[j];
        }
        // insert `nums2[i]`.
        nums1[index] = nums2[i];
        // increase length of nums1.
        len1++;
    }
}

int main(int argc, char **argv)
{
    int nums1_1[] = { 1, 2, 3, 0, 0, 0 }, len1_1 = 3, size1_1 = sizeof(nums1_1) / sizeof(int);
    int nums2_1[] = { 2, 5, 6 },          len2_1 = sizeof(nums2_1) / sizeof(int);
    int nums1_2[] = { 1, 0 },             len1_2 = 1, size1_2 = sizeof(nums1_2) / sizeof(int);
    int nums2_2[] = { 2 },                len2_2 = sizeof(nums2_2) / sizeof(int);
    struct Object inputs[] = {
        { .nums1 = nums1_1, .nums2 = nums2_1, .len1 = len1_1, .size1 = size1_1, .len2 = len2_1 },
        { .nums1 = nums1_2, .nums2 = nums2_2, .len1 = len1_2, .size1 = size1_2, .len2 = len2_2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums1 = inputs[i].nums1;
        int m = inputs[i].len1;
        int size = inputs[i].size1;
        int *nums2 = inputs[i].nums2;
        int n = inputs[i].len2;
        printf("\n nums1 = ");
        print_nums(nums1, size);
        printf(", m = %d\n", m);
        printf(" nums2 = ");
        print_nums(nums2, n);
        printf(", n = %d\n", n);

        merge(nums1, m, nums2, n);
        printf(" Output: ");
        print_nums(nums1, size);
        printf("\n");
    }

    return EXIT_SUCCESS;
}
