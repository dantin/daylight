# -*- coding: utf-8 -*-

def dfs(mset, start, end, outer_sum, inner_sum):
    if start >= end:
        return False
    if outer_sum == inner_sum:
        return True

    return (
            dfs(mset, start + 1, end, outer_sum + mset[start], inner_sum - mset[start]) or
            dfs(mset, start, end - 1, outer_sum + mset[end], inner_sum - mset[end]))


def can_partition(mset):
    if not mset:
        return True

    total = sum(mset)
    if total % 2 == 1:
        return False

    mset.sort()

    return dfs(mset, 0, len(mset) - 1, 0, total)


if __name__ == '__main__':
    inputs = [
        [15, 5, 20, 10, 35, 15, 10],
    ]

    for nums in inputs:
        print(' Input: {}'.format(nums))
        can = can_partition(nums)
        print(' Output: {}'.format(can))

