# -*- coding: utf-8 -*-

import random

class Solution():

    def crack(self, stream):
        choosen = None

        for i, e in enumerate(stream):
            if i == 0:
                choosen = e
            elif random.randint(1, i + 1) == 1:
                choosen = e

        return choosen


if __name__ == '__main__':
    inputs = [random.randint(1, 1000) for _ in range(1000)]

    solver = Solution()
    print(' Output:', solver.crack(inputs))
