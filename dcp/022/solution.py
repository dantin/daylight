# -*- coding: utf-8 -*-

class Solution():

    def crack(self, s, word_dict):
        res = []
        if len(s) == 0 or not word_dict:
            return res
        self.dfs(s, word_dict, [], res)
        return res

    def dfs(self, s, word_dict, words, res):
        if self.check(s, word_dict):
            if len(s) == 0:
                res.append(list(x for x in words))

            for i in range(1, len(s) + 1):
                if s[:i] in word_dict:
                    words.append(s[:i])
                    self.dfs(s[i:], word_dict, words, res)
                    words.pop()

    def check(self, s, word_dict):
        dp = [False for i in range(len(s) + 1)]
        dp[0] = True
        for i in range(len(s) + 1):
            for k in range(i):
                if dp[k] and s[k:i] in word_dict:
                    dp[i] = True
        return dp[len(s)]


if __name__ == '__main__':
    inputs = [
        dict(s='catsanddog', word_dict=['cat', 'cats', 'and', 'sand', 'dog']),
    ]
    for i in inputs:
        s, word_dict = i['s'], i['word_dict']

        print(' Input: s = {}, word_dict={}'.format(s, word_dict))
        solver = Solution()
        ans = solver.crack(s, word_dict)
        print(' Output: {}'.format(ans))
