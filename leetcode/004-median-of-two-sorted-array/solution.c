#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, const char *argv[])
{
    int r1[] = {1};
    int r2[] = {2};

    int n1 = sizeof(r1)/sizeof(r1[0]);
    int n2 = sizeof(r2)/sizeof(r2[0]);

    printf("Median is 1.5 = %f\n", find_median_sorted_arrays(r1, n1, r2, n2));

    return 0;
}
