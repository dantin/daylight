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
        idx, value = 0, 1
        elems = [(i, num) for i, num in enumerate(nums)]
        elems.sort(key=lambda x: x[value])
        low, high = 0, len(nums) - 1
        while low < high:
            diff = target - elems[low][value]
            if diff > elems[high][value]:
                while low + 1 < len(nums) and elems[low][value] == elems[low + 1][value]: low += 1
                low += 1
            elif diff < elems[high][value]:
                while high - 1 >= 0 and elems[high][value] == elems[high - 1][value]: high -= 1
                high -= 1
            else:
                return [elems[low][idx], elems[high][idx]]
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
        pos = solution.twoSum2(nums, target)
        print(' Output: ', pos, sep='')
