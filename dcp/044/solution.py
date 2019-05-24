# -*- coding: utf-8 -*-

class Solution():

    def crack(self, nums):
        _, count = self.merge_sort(nums)
        return count

    def merge_sort(self, nums):
        if not nums or len(nums) == 1:
            return nums, 0

        mid = len(nums) // 2
        merged_nums, count = self.merge(
            self.merge_sort(nums[:mid]), self.merge_sort(nums[mid:]))

        return merged_nums, count

    def merge(self, lhs, rhs):
        i, j = 0, 0
        merged = []
        lhs_nums, lhs_size = lhs
        rhs_nums, rhs_size = rhs
        count = lhs_size + rhs_size

        while i < len(lhs_nums) and j < len(rhs_nums):
            if lhs_nums[i] < rhs_nums[j]:
                merged.append(lhs_nums[i])
                i += 1
            else:
                merged.append(rhs_nums[j])
                count += len(lhs_nums[i:])
                j += 1

        while i < len(lhs_nums):
            merged.append(lhs_nums[i])
            i += 1
        while j < len(rhs_nums):
            merged.append(rhs_nums[j])
            j += 1

        return merged, count


if __name__ == '__main__':
    inputs = [
        [2, 1, 3, 4, 5],
        [2, 4, 1, 3, 5],
    ]

    for nums in inputs:
        print('\n Input: {}'.format(nums))

        solver = Solution()
        count = solver.crack(nums)
        print(' Output: {}'.format(count))
