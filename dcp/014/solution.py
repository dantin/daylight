# -*- coding: utf-8 -*-

import datetime
import math
import random


class Solution():

    def __init__(self):
        random.seed(datetime.datetime.now())

    def crack(self, prec=3):
        inside, total, diff = 0, 0, 1
        scale = 10 ** (prec)
        base = int(float('{0:.{prec}f}'.format(math.pi, prec=prec)) * scale)
        while diff != 0:
            x2 = random.random() ** 2
            y2 = random.random() ** 2

            if x2 + y2 < 1.0:
                inside += 1
            total += 1
            pi = float(inside) / total * 4
            diff = int(pi * scale) - base

        return float('{0:.{prec}f}'.format(pi, prec=prec)) 


if __name__ == '__main__':
    solver = Solution()
    print(solver.crack(5))
