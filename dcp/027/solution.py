# -*- coding: utf-8 -*-

class Solution():

    def crack(self, s):
        stack = []
        for c in s:
            if c in ('(', '[', '{'):
                stack.append(c)
            elif c == ')':
                if (not stack) or stack.pop() != '(':
                    return False
            elif c == ']':
                if (not stack) or stack.pop() != '[':
                    return False
            elif c == '}':
                if (not stack) or stack.pop() != '{':
                    return False
        if stack:
            return False
        else:
            return True


if __name__ == '__main__':
    inputs = [
        '([])[]({})',
        '([)]',
        '((()',
    ]

    for s in inputs:
        print()
        print(' Input: \'{}\''.format(s))
        solver = Solution()
        print(' Output:', solver.crack(s))
