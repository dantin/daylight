# -*- coding: utf-8 -*-


def max_sum1(nums, i):
    if i == 0:
        return nums[0]
    if i == 1:
        return max(nums[0], nums[1])
    return max(max_sum1(nums, i - 1), nums[i] + max_sum1(nums, i - 2))


def max_sum(nums, i, dp):
    if i == 0:
        return nums[0]
    if i == 1:
        return max(nums[0], nums[1])
    if dp[i]:
        return dp[i]
    dp[i] = max(max_sum(nums, i - 1, dp), nums[i] + max_sum(nums, i - 2, dp))
    return dp[i]


class Solution():

    def crack1(self, nums):
        return max_sum1(nums, len(nums) - 1)

    def crack2(self, nums):
        dp = [None for _ in range(len(nums))]
        return max_sum(nums, len(nums) - 1, dp)

    def crack(self, nums):
        pprev, prev, curr = 0, 0, 0
        for i in range(len(nums)):
            if i == 0:
                curr = nums[0]
            elif i == 1:
                curr = max(nums[0], nums[1])
            else:
                curr = max(prev, nums[i] + pprev)

            pprev, prev = prev, curr
        return curr


if __name__ == '__main__':
    inputs = [
        [2, 4, 6, 2, 5],
        [5, 1, 1, 5],
    ]

    for nums in inputs:
        print('\n Input:', nums)
        solver = Solution()
        max_num = solver.crack(nums)
        print(' Output: ', max_num)
