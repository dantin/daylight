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
        idx_pos, val_pos = 0, 1
        objs = [(i, num) for i, num in enumerate(nums)]
        objs.sort(key=lambda x: x[val_pos])
        low, high = 0, len(nums) - 1
        while low < high:
            diff = target - objs[low][val_pos]
            if diff > objs[high][val_pos]:
                while low + 1 < high and objs[low][val_pos] == objs[low + 1][val_pos]: low += 1
                low += 1
            elif diff < objs[high][val_pos]:
                while high - 1 >= low and objs[high][val_pos] == objs[high - 1][val_pos]: high -= 1
                high -= 1
            else:
                return [objs[low][idx_pos], objs[high][idx_pos]]
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
