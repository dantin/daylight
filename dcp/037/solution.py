# -*- coding: utf-8 -*-

def power_set(elements):
    result = []
    for s in subsets(elements):
        result.append(s)
    return result


def subsets(elements):
    if not elements:
        return

    # Binary representation of integers is as
    # {000, 001, 010, 011, 100, 101, 110, 111} for numbers ranging from
    # 0 to 7.
    # For an integer counter value, considering 1 as inclusion of
    # corresponding element in collection and '0' as exclusion we can
    # generate subsets based on the counting sequence.
    size = len(elements)
    for max_int in range(0x1 << size):
        subset = []
        for i in range(size):
            if max_int & (0x1 << i):
                subset.append(elements[i])
        yield subset


if __name__ == '__main__':
    inputs = [
        [1, 2, 3],
    ]

    for nums in inputs:
        print()
        print(' Input:', nums)

        result = power_set(nums)
        print(' Output:', result)
