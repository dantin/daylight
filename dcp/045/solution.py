# -*- coding: utf-8 -*-

import random


def rand5():
    return random.randint(1, 5)


def rand7():
    while True:
        num = 5 * (rand5() - 1) + (rand5() - 1)
        if num < 21:
            return num % 7 + 1


if __name__ == '__main__':
    count = 10 ** 6
    result_dict = {}
    for _ in range(count):
        num = rand7()
        if num not in result_dict:
            result_dict[num] = 0
        result_dict[num] += 1

    print('\n Output:')
    for num, freq in sorted(result_dict.items()):
        print('  {}: {}, probability: {}'.format(num, freq, freq / count))
