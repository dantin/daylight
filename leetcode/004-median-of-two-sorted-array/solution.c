#include <stdio.h>
#include <stdlib.h>

struct object {
    int *nums1;
    int n1;
    int *nums2;
    int n2;
};

void print_array(int *array, int len)
{
    int i;

    putchar('[');
    for (i = 0; i < len; i++) {
        if (i == 0) {
            printf("%d", array[i]);
        } else {
            printf(", %d", array[i]);
        }
    }
    putchar(']');
}

double find_kth(int a[], int alen, int b[], int blen, int k)
{
    // Always assume that alen is equal or smaller than blen
    if (alen > blen) {
        return find_kth(b, blen, a, alen, k);
    }

    if (alen == 0) {
        return b[k-1];
    }

    if (k == 1) {
        return a[0] < b[0] ? a[0] : b[0];
    }

    // Divide k into two parts
    int ia = k/2 < alen ? k/2 : alen;
    int ib = k - ia;
    if (a[ia-1] < b[ib-1]) {
        // a[ia-1] must be ahead of k-th
        return find_kth(a+ia, alen-ia, b, blen, k-ia);
    } else if (a[ia-1] > b[ib-1]) {
        // b[ib-1] must be ahead of k-th
        return find_kth(a, alen, b+ib, blen-ib, k-ib);
    } else {
        return a[ia-1];
    }
}

double find_median_sorted_arrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    int half = (nums1Size + nums2Size) / 2;
    if ((nums1Size + nums2Size) & 0x1) {
        return find_kth(nums1, nums1Size, nums2, nums2Size, half + 1);
    } else {
        double l = find_kth(nums1, nums1Size, nums2, nums2Size, half);
        double r = find_kth(nums1, nums1Size, nums2, nums2Size, half + 1);
        return (l + r) / 2;
    }
}

int main(int argc, const char **argv)
{
    int arr1[] = {1, 3}, len1 = sizeof(arr1) / sizeof(int);
    int arr2[] = {2},    len2 = sizeof(arr2) / sizeof(int);
    int arr3[] = {1, 2}, len3 = sizeof(arr3) / sizeof(int);
    int arr4[] = {3, 4}, len4 = sizeof(arr4) / sizeof(int);

    struct object inputs[] = {
        {.nums1 = arr1, .n1 = len1, .nums2 = arr2, .n2 = len2},
        {.nums1 = arr3, .n1 = len3, .nums2 = arr4, .n2 = len4},
    };
    int i, len = sizeof(inputs)/sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums1 = inputs[i].nums1;
        int *nums2 = inputs[i].nums2;
        int n1 = inputs[i].n1;
        int n2 = inputs[i].n2;

        printf("\n nums1: "); print_array(nums1, n1); putchar('\n');
        printf(" nums2: "); print_array(nums2, n2); putchar('\n');

        printf(" Median = %f\n", find_median_sorted_arrays(nums1, n1, nums2, n2));
    }

    return EXIT_SUCCESS;
}
