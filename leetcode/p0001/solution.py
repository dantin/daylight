# -*- coding: utf-8 -*-


class Solution:

    def twoSum(self, nums: list, target: int) -> list:
        cache = {}
        for i, num in enumerate(nums):
            if num in cache and i != cache[num]:
                return [i, cache[num]]
            cache[target - num] = i
        return []

    def twoSum2(self, nums: list, target: int) -> list:
        objs = [(i, num) for i, num in enumerate(nums)]
        objs.sort(key=lambda x: x[1])
        low, high = 0, len(nums) - 1
        while low < high:
            diff = target - objs[low][1]
            if diff > objs[high][1]:
                while low + 1 < high and objs[low][1] == objs[low + 1][1]: low += 1
                low += 1
            elif diff < objs[high][1]:
                while high - 1 >= low and objs[high][1] == objs[high - 1][1]: high -= 1
                high -= 1
            else:
                return [objs[low][0], objs[high][0]]
        return []


if __name__ == '__main__':
    inputs = [
        ([2, 7, 11, 15], 9)
    ]

    for nums, target in inputs:
        print(' Given nums: ', nums, ', target = ', target, sep='')
        solution = Solution()
        pos = solution.twoSum(nums, target)
        print(' Output 1: ', pos, sep='')
        pos = solution.twoSum2(nums, target)
        print(' Output 2: ', pos, sep='')
