# -*- coding: utf-8 -*-


def max_subarray(nums):
    if not nums or max(nums) < 0:
        return 0

    current_max_sum = nums[0]
    overall_max_sum = nums[0]

    for n in nums[1:]:
        current_max_sum = max(n, current_max_sum + n)
        overall_max_sum = max(overall_max_sum, current_max_sum)

    return overall_max_sum


if __name__ == '__main__':
    inputs = [
        [34, -50, 42, 14, -5, 86],
        [-5, -1, -8, -9],
        [44, -5, 42, 14, -150, 86],
    ]

    for nums in inputs:
        print('\n Input: {}'.format(nums))
        s = max_subarray(nums)
        print(' Output: {}'.format(s))
