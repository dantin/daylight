# -*- coding: utf-8 -*-

class Solution:
    def longestPalindrome(self, s: str) -> str:
        # Manacher
        size = len(s)
        if size < 2:
            return s

        t = '#{}#'.format('#'.join(s))
        t_len = len(t)
        p = [0 for _ in range(t_len)]
        
        max_right = 0 # right position
        center = 0    # center position

        max_len = 1  # max length of palindrome
        start = 1    # start position of max palindrome

        for i in range(t_len):
            if i < max_right:
                mirror = 2 * center - i
                p[i] = min(max_right - i, p[mirror])
            # expands endpoints
            left = i - (1 + p[i])
            right = i + (1 + p[i])
            while left >=0 and right < t_len and t[left] == t[right]:
                p[i] += 1
                left -= 1
                right += 1
            # update positions, start point and max length.
            if i + p[i] > max_right:
                max_right = i + p[i]
                center = i
            if p[i] > max_len:
                max_len = p[i]
                start = (i - max_len) // 2

        return s[start:start + max_len]


if __name__ == '__main__':
    inputs = [
        'babad',
        'cbbd',
    ]
    solution = Solution()

    for s in inputs:
        print(' Input: "{}"'.format(s))
        print(' Output: "{}"'.format(solution.longestPalindrome(s)))
