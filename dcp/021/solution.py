# -*- coding: utf-8 -*-

import heapq

class Solution():

    def crack(self, intervals):
        intervals.sort(key=lambda k:k[0])
        heap = []
        for interval in intervals:
            if heap and interval[0] >= heap[0]:
                heapq.heappop(heap)
                heapq.heappush(heap, interval[1])
            else:
                heapq.heappush(heap, interval[1])

        return len(heap) 


if __name__ == '__main__':
    inputs = [
        [(30, 75), (0, 50), (60, 150)],
    ]

    for intervals in inputs:
        print(' Input:', intervals)
        solver = Solution()
        rooms = solver.crack(intervals)
        print(' Output:', rooms)

