# -*- coding: utf-8 -*-


class Solution():
    def crack(self, nums):
        """
        Time Complexity:  O(n)
        Space Complexity: O(n)
        Auxiliary Space:  O(1)
        """
        def segregate(nums):
            fast, slow = 0, 0
            while fast < len(nums):
                if nums[fast] <= 0:
                    tmp = nums[fast]
                    nums[fast] = nums[slow]
                    nums[slow] = tmp
                    slow += 1
                fast += 1
            return slow

        def find_missing_positive(nums):
            for i in range(len(nums)):
                if (abs(nums[i]) - 1 < len(nums) and nums[abs(nums[i]) - 1] > 0):
                    nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1]

            for i in range(len(nums)):
                if nums[i] > 0:
                    return i + 1
            return len(nums) + 1

        # separate positive and negative numbers
        pivot = segregate(nums)
        # find missing positive
        return find_missing_positive(nums[pivot:])


    def crack1(self, nums):
        """
        Time Complexity:  O(n)
        Space Complexity: O(n)
        Auxiliary Space:  O(n)
        """
        m = max(nums)
        if m < 1:
            return 1
        if len(nums) == 1:
            return 2 if nums[0] == 1 else 1

        exists = [False] * m  # tmp indicates whether item was found or not
        for i in range(len(nums)):
            if nums[i] > 0:
                if not exists[nums[i] - 1]:
                    exists[nums[i] - 1] = True
        for i in range(len(exists)):
            if not exists[i]:
                return i + 1
        return i + 2


if __name__ == '__main__':
    inputs = [
        dict(nums=[3, 4, -1, 1]),
        dict(nums=[1, 2, 0]),
    ]
    for i in inputs:
        nums = i['nums']
        print(' Input:', nums)
        solver = Solution()
        print(' Output:', solver.crack(nums))
        print(' Output:', solver.crack1(nums))
