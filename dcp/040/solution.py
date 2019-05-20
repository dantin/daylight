# -*- coding: utf-8 -*-


class Solution():

    def crack(self, nums, word_size=32):
        target = 0

        for i in range(word_size):
            sum_bits = 0
            x = 1 << i
            for j in range(len(nums)):
                if nums[j] & x:
                    sum_bits += 1

            if sum_bits % 3:
                target |= x

        return target



if __name__ == '__main__':
    inputs = [
        [6, 1, 3, 3, 3, 6, 6],
        [13, 19, 13, 13],
    ]

    for nums in inputs:
        print('\n Input: {}'.format(nums))

        solver = Solution()
        target = solver.crack(nums)

        print(' Output: {}'.format(target))
