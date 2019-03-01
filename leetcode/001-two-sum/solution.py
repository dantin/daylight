# -*- coding: utf-8 -*-


class Solution:

    def twoSum(self, nums: list, target: int) -> list:
        cache = {}
        for i, num in enumerate(nums):
            if num in cache and i != cache[num]:
                return [i, cache[num]]
            cache[target - num] = i
        return []


if __name__ == '__main__':
    inputs = [
        ([2, 7, 11, 15], 9)
    ]

    for nums, target in inputs:
        print(' Given nums: ', nums, ', target = ', target, sep='')
        solution = Solution()
        pos = solution.twoSum(nums, target)
        print(' Output: ', pos, sep='')
