# -*- coding: utf-8 -*-

class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if numRows <= 1:
            return s

        ret = ''
        for row in range(numRows):
            interval1 = numRows + (numRows - 2) - row * 2
            interval2 = row * 2
            flag = False
            i = row
            while i < len(s):
                ret += s[i]
                delta = 0
                first_pass = True
                while first_pass or (delta == 0):
                    first_pass = False
                    delta = interval1 if not flag else interval2
                    flag = not flag
                i += delta

        return ret


if __name__ == '__main__':
    inputs = [
        ('PAYPALISHIRING', 3),
        ('PAYPALISHIRING', 4),
    ]
    solution = Solution()

    for s, numRows in inputs:
        print(' Input: s = "{}", numRows = {}'.format(s, numRows))
        o = solution.convert(s, numRows)
        print(' Output: "{}"'.format(o))
