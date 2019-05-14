# -*- coding: utf-8 -*-

class Solution():

    def is_palindrome(self, s):
        return s[::-1] == s

    def crack(self, s):
        if self.is_palindrome(s):
            return s

        if s[0] == s[-1]:
            return s[0] + self.crack(s[1:-1]) + s[-1]

        pal_1 = s[0] + self.crack(s[1:]) + s[0]
        pal_2 = s[-1] + self.crack(s[:-1]) + s[-1]

        if len(pal_1) > len(pal_2):
            return pal_2
        elif len(pal_1) < len(pal_2):
            return pal_1
        return pal_1 if pal_1 < pal_2 else pal_2


if __name__ == '__main__':
    inputs = [
        'race',
        'google',
    ]

    for s in inputs:
        print()
        print(' Input:', s)

        solver = Solution()
        print(' Output:', solver.crack(s))
