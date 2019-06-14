# -*- coding: utf-8 -*-

def pow(x, y):
    if not x:
        return 0
    elif not y:
        return 1

    y_abs = abs(y)

    prev_result, prev_exp = 0, 0
    curr_exp, result = 1, x
    while curr_exp <= y_abs:
        prev_result, prev_exp = result, curr_exp
        result *= result
        curr_exp *= 2

    prev_result *= pow(x, y_abs - prev_exp)

    return 1/prev_result if y != y_abs else prev_result


if __name__ == '__main__':
    inputs = [
        (2, 2),
        (2, 10),
    ]
    for x, y in inputs:
        print('\n Input: pow({}, {})'.format(x, y))
        res = pow(x, y)
        print(' Output: {}'.format(res))
