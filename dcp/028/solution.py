# -*- coding: utf-8 -*-

class Solution():

    def crack(self, words, width):
        lines = []
        i = 0
        while i < len(words):
            begin = i
            line_width = 0
            while i < len(words):
                curr = len(words[i]) if line_width == 0 else line_width + len(words[i]) + 1
                if curr > width:
                    break
                line_width = curr
                i += 1

            token_size = i - begin - 1
            padding_count = width - line_width
            padding_each = 0
            if (token_size > 0) and (i < len(words)):
                padding_each = padding_count // token_size
                padding_count %= token_size

            j = begin
            line = ''
            while j < i:
                if j == begin:
                    line = words[j]
                else:
                    line += ' ' * (padding_each + 1)
                    if padding_count > 0 and i < len(words):
                        line += ' '
                        padding_count -= 1
                    line += words[j]
                j += 1
            if padding_count > 0:
                line += ' ' * padding_count
            lines.append(line)

        return lines


if __name__ == '__main__':
    inputs = [
        dict(words=['the', 'quick', 'brown', 'fox', 'jumps', 'over', 'the', 'lazy', 'dog'], k = 16),
    ]

    for i in inputs:
        words, k = i['words'], i['k']
        print(' Input:')
        print('  words:', words)
        print('  k:', k)

        solver = Solution()
        content = solver.crack(words, k)
        print(' Output:')
        for line in content:
            print(line)
