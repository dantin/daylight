# -*- coding: utf-8 -*-


def two_sum(nums, target):
    if ((nums is None)
            or not isinstance(nums, list)
            or len(nums) == 0):
        return False

    nums.sort()
    low, high = 0, len(nums) - 1
    while low < high:
        total = nums[low] + nums[high]
        if total < target:
            while low + 1 < high and nums[low] == nums[low + 1]: low += 1
            low += 1
        elif total > target:
            while high - 1 >= low and nums[high - 1] == nums[high]: high -= 1
            high -= 1
        else:
            return True

    return False


if __name__ == '__main__':
    nums = [10, 15, 3, 7]
    k = 17
    print(' Input:', nums, sep=' ')
    print(' Target: ', k, sep=' ')
    found = two_sum(nums, k)
    print('', 'found' if found else 'NOT found')
