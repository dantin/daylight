# -*- coding: utf-8 -*-

class Solution:
    def findMedianSortedArrays(self, nums1, nums2) -> float:
        half = (len(nums1) + len(nums2)) // 2
        if (len(nums1) + len(nums2)) & 0x1 == 0:
            lhs = find_kth(nums1, nums2, half)
            rhs = find_kth(nums1, nums2, half + 1)
            return (lhs + rhs) / 2
        else:
            return find_kth(nums1, nums2, half + 1)

def find_kth(nums1, nums2, k):
    # Always assume the length of nums1 is equal or smaller than that of nums2.
    if len(nums1) > len(nums2):
        return find_kth(nums2, nums1, k)

    if len(nums1) == 0:
        return nums2[k - 1]

    if k == 1:
        return min(nums1[0], nums2[0])

    # Divide k into two parts.
    ia = min(k // 2, len(nums1))
    ib = k - ia
    if nums1[ia - 1] < nums2[ib - 1]:
        return find_kth(nums1[ia:], nums2, k - ia)
    elif nums1[ia - 1] > nums2[ib - 1]:
        return find_kth(nums1, nums2[ib:], k - ib)
    else:
        return nums1[ia - 1]


if __name__ == '__main__':
    inputs = [
        ([], [2, 3]),
        ([1, 3], [2]),
        ([1, 3], [2, 4]),
    ]
    s = Solution()

    for nums1, nums2 in inputs:
        print(' nums1 = {}'.format(nums1))
        print(' nums2 = {}'.format(nums2))

        median = s.findMedianSortedArrays(nums1, nums2)

        print('The median is {}\n'.format(median))
