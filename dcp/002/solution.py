# -*- coding: utf-8 -*-


class Solution():
    """Algorithm:
    1. Construct `left`, with `left[i]` contains product of all elements on `left` of `nums[i]` excluding
       `nums[i]`
    2. Construct `right`, with `right[i]` contains product of all elements on `right` of `nums[i]`
       excluding `nums[i]`
    3. return multiply of `left` and `right`
    """

    def crack(self, nums):
        """
        Time Complexity:  O(n)
        Space Complexity: O(n)
        Auxiliary Space:  O(1)
        """
        prod = [1 for _ in range(len(nums))]

        tmp = 1
        for i in range(len(nums)):
            prod[i] = tmp
            tmp *= nums[i]

        tmp = 1
        for i in reversed(range(len(nums))):
            prod[i] *= tmp
            tmp *= nums[i]

        return prod


    def crack2(self, nums):
        """
        Time Complexity:  O(n)
        Space Complexity: O(n)
        Auxiliary Space:  O(n)
        """
        left, right = [1 for _ in range(len(nums))], [1 for _ in range(len(nums))]

        for i in range(1, len(nums)):
            left[i] = nums[i - 1] * left[i - 1]

        for i in reversed(range(0, len(nums) - 1)):
            right[i] = nums[i + 1] * right[i + 1]

        return [lhs * rhs for (lhs, rhs) in zip(left, right)]


if __name__ == '__main__':
    inputs = [
        dict(nums=[1, 2, 3, 4, 5] ),
        dict(nums=[3, 2, 1]),
    ]

    for data in inputs:
        print()
        nums = data['nums']
        solver = Solution()
        print(' Input:', nums)
        answer = solver.crack(nums)
        print(' Output:', answer)
