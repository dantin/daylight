# -*- coding: utf-8 -*-


class Solution():

    def crack(self, s):
        if not s:
            return 0

        dp = [0 for _ in range(len(s) + 1)]
        dp[0] = 1
        dp[1] = 0 if s[0] == '0' else 1
        for i in range(2, len(s) + 1):
            if s[i - 1] != '0':
                dp[i] = dp[i - 1]
            num = int(s[i - 2:i])
            if num >= 10 and num <= 26:
                dp[i] += dp[i - 2]

        return dp[len(s)]


if __name__ == '__main__':
    inputs = [
        '111',
        '12',
        '226',
    ]
    for s in inputs:
        print()
        solver = Solution()
        print(' Input:', s)
        print(' Output:', solver.crack(s))
