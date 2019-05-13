# -*- coding: utf-8 -*-

import heapq as hq


class Solution():

    def crack(self, nums):
        if not nums:
            return None

        min_heap, max_heap = [], []
        medians = []

        for n in nums:
            hq.heappush(min_heap, n)
            if len(min_heap) > len(max_heap) + 1:
                smallest_large_element = hq.heappop(min_heap)
                hq.heappush(max_heap, -smallest_large_element)

            if len(min_heap) == len(max_heap):
                median = (min_heap[0] - max_heap[0]) / 2
            else:
                median = min_heap[0]
            medians.append(median)

        return medians


if __name__ == '__main__':
    inputs = [
        dict(nums=[2, 5]),
        dict(nums=[2, 1, 5, 7, 2, 0, 5]),
    ]

    for i in inputs:
        nums = i['nums']

        print(' Input:')
        print('  nums:', nums)

        solver = Solution()
        medians = solver.crack(nums)
        print(' Output:', medians)
