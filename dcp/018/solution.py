# -*- coding: utf-8 -*-

class Solution():

    def crack(self, nums, k):
        window = []  # sliding window
        choosen = []

        for i in range(k):
            while window and (nums[window[-1]] <= nums[i]):
                window.pop()
            window.append(i)

        for i in range(k, len(nums)):
            choosen.append(nums[window[0]])
            while window and window[0] <= i - k:
                window.pop(0)
            while window and (nums[window[-1]] <= nums[i]):
                window.pop()
            window.append(i)

        choosen.append(nums[window[0]])
        return choosen


if __name__ == '__main__':
    inputs = [
        dict(nums=[1, 2, 3, 2, 4, 1, 5, 6, 1], k=3),
        dict(nums=[10, 5, 2, 7, 8, 7], k=3),
    ]

    for i in inputs:
        nums, k = i['nums'], i['k']
        print(' Input: nums = ', nums, ', k = ', k, sep='')
        solver = Solution()
        array = solver.crack(nums, k)
        print(' Output:', array, end='\n\n')
