# -*- coding: utf-8 -*-

import sys


def crack(prices):
    if not prices or len(prices) < 2:
        return None

    min_price = prices[0]
    max_diff = -sys.maxsize

    for p in prices[1:]:
        if p - min_price > max_diff:
            max_diff = p - min_price
        if p < min_price:
            min_price = p

    return max_diff


if __name__ == '__main__':
    inputs = [
        [ 9, 11, 8, 5, 7, 10 ],
    ]

    for prices in inputs:
        print('\n Input: {}'.format(prices))

        max_profit = crack(prices)

        print(' Output: {}'.format(max_profit))
