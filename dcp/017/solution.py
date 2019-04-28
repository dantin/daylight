# -*- coding: utf-8 -*-


class Node():
    def __init__(self, level, length):
        self.level = level
        self.length = length


class Solution():

    def crack(self, content):
        if (content is None) or (not content):
            return 0

        count = 0
        stack = []
        for row in content.split('\n'):
            level = row.count('\t') 
            while stack and level <= stack[-1].level:
                stack.pop()
            if '.' in row:
                # found file.
                if not stack:
                    count = max(count, len(row) - level)
                else:
                    count = max(count, stack[-1].length + len(row) - level)
            else:
                # meet directory.
                if not stack:
                    stack.append(Node(level, len(row) - level + 1))
                else:
                    stack.append(Node(level, stack[-1].length + len(row) - level + 1))

        return count


if __name__ == '__main__':
    inputs = [
        'dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext',
        'dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext',
    ]
    for content in inputs:
        print(' Input:\n', content, sep='')
        solver = Solution()
        print(' Output:', solver.crack(content))
        print()
