# -*- coding: utf-8 -*-


def is_palindrome(s):
    return s == s[::-1]


def longest_palindrome_substring(s):
    if not s or is_palindrome(s):
        return s

    s1 = longest_palindrome_substring(s[1:])
    s2 = longest_palindrome_substring(s[:-1])

    return s1 if len(s1) >= len(s2) else s2


if __name__ == '__main__':
    inputs = [
        'aabcdcb',
        'bananas',
    ]

    for s in inputs:
        print('\n Input: \'{}\''.format(s))

        subs = longest_palindrome_substring(s)

        print(' Output: \'{}\''.format(subs))
