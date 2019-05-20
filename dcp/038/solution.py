# -*- coding: utf-8 -*-

class Solution():

    def is_valid(self, board, row):
        if row in board:
            return False

        col = len(board)
        for occupied_col, occupied_row in enumerate(board):
            if abs(occupied_row - row) == abs(occupied_col - col):
                return False

        return True

    def put_queen(self, board, n):
        if n == len(board):
            return 1

        count = 0
        for row in range(n):
            if self.is_valid(board, row):
                count += self.put_queen(board + [row], n)

        return count


    def crack(self, n):
        return self.put_queen([], n)


if __name__ == '__main__':
    inputs = [
        8,
    ]

    for n in inputs:
        print()
        print(' Input:', n)

        solver = Solution()
        count = solver.crack(n)
        print(' Output:', count)
