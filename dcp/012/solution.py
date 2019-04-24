# -*- coding: utf-8 -*-

class Solution():

    def crack(self, n, X):
        dp = [0 for _ in range(n + 1)]
        dp[0] = 1
        for i in range(n + 1):
            dp[i] += sum(dp[i - x] for x in X if i - x > 0)
            dp[i] += 1 if i in X else 0
        return dp[-1]


if __name__ == '__main__':
    inputs = [
        dict(n=4, X=[1, 2]),
        dict(n=10, X=[1, 3, 5]),
    ]
    for i in inputs:
        n, X = i['n'], i['X']
        print(' n = ', n, ', X = ', X, sep='')

        solver = Solution()
        print(' Output:', solver.crack(n, X))
