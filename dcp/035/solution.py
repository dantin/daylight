# -*- coding: utf-8 -*-

class Solution():

    def crack(self, arr):
        last_idx = self.move_to_front(arr, 0, len(arr) - 1, 'R')
        self.move_to_front(arr, last_idx + 1, len(arr) - 1, 'G')

        return arr

    def move_to_front(self, arr, start, end, target):
        i, j = start, end
        idx = -1

        while i < j:
            if arr[i] == target:
                idx = i
                i += 1
            elif arr[j] != target:
                j -= 1
            else:
                idx = i
                arr[i], arr[j] = arr[j], arr[i]

        return idx


if __name__ == '__main__':
    inputs = [
        ['G', 'B', 'R', 'R', 'B', 'R', 'G'],
    ]

    for elems in inputs:
        print()
        print(' Input:', elems)

        solver = Solution()
        arr = solver.crack(elems)
        print(' Output:', arr)
