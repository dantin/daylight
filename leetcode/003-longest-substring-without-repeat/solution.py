# -*- coding: utf-8 -*-

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        window = {}
        start_pos = 0
        max_len = 0
        for i, v in enumerate(s):
            if v in window:
                start_pos = max(start_pos, window[v] + 1)
            window[v] = i
            max_len = max(max_len, i - start_pos + 1)
        return max_len


if __name__ == '__main__':
    inputs = ['abcabcbb', 'bbbbb', 'pwwkew']
    s = Solution()

    for st in inputs:
        print(' Input: "{}"'.format(st))

        res = s.lengthOfLongestSubstring(st)

        print(' Output: {}\n'.format(res))
