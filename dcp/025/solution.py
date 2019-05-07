# -*- coding: utf-8 -*-

class Solution():

    def crack(self, s, p):
        dp = [[False for i in range(len(p) + 1)] for _ in range(len(s) + 1)]
        dp[0][0] = True
        for i in range(1, len(p) + 1):
            if p[i - 1] == '*':
                if i >= 2:
                    dp[0][i] = dp[0][i - 2]
        for i in range(1, len(s) + 1):
            for j in range(1, len(p) + 1):
                if p[j - 1] == '.':
                    dp[i][j] = dp[i - 1][j - 1]
                elif p[j - 1] == '*':
                    dp[i][j] = dp[i][j - 1] or dp[i][j - 2] or (dp[i - 1][j] and (s[i - 1] == p[j - 2] or p[j - 2] == '.'))
                else:
                    dp[i][j] = dp[i - 1][j - 1] and s[i - 1] == p[j - 1]

        return dp[len(s)][len(p)]


if __name__ == '__main__':
    inputs = [
        dict(p='ra.', s='ray'),
        dict(p='.*at', s='chat'),
        dict(p='.*at', s='chats'),
    ]

    for i in inputs:
        s, p = i['s'], i['p']
        print(' Input: s = \'{}\', p = \'{}\''.format(s, p))
        solver = Solution()
        print(' Output: ', solver.crack(s, p))
