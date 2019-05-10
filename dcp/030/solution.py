# -*- coding: utf-8 -*-

class Solution():

    def crack(self, nums):
        leftmosthigh = [0] * len(nums)
        leftmax = 0
        for i in range(len(nums)):
            if nums[i] > leftmax:
                leftmax = nums[i]
            leftmosthigh[i] = leftmax

        total = 0
        rightmax = 0
        for i in reversed(range(len(nums))):
            if nums[i] > rightmax:
                rightmax = nums[i]
            if min(rightmax, leftmosthigh[i]) > nums[i]:
                total += min(rightmax, leftmosthigh[i]) - nums[i]
        return total


if __name__ == '__main__':
    inputs = [
        [2, 1, 2],
        [3, 0, 1, 3, 0, 5],
    ]

    for nums in inputs:
        print()
        print(' Input:', nums)

        solver = Solution()
        units = solver.crack(nums)

        print(' Output:', units)
