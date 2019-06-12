# -*- coding: utf-8 -*-

def dfs(nums, target, start, end):
    if start == end:
        return

    mid = start + ((end - start) // 2)

    if nums[mid] == target:
        return mid
    elif nums[mid] > target:
        if nums[start] >= target:
            return dfs(nums, target, start, mid)
        else:
            return dfs(nums, target, mid, end)
    elif nums[mid] < target:
        if nums[start] <= target:
            return dfs(nums, target, start, mid)
        else:
            return dfs(nums, target, mid, end)


def find_element(nums, target):
    return dfs(nums, target, 0, len(nums))


if __name__ == '__main__':
    nums = [13, 18, 25, 2, 8, 10]
    target = 8

    print(' Input:  {}'.format(nums))
    print(' Target: {}'.format(target))

    pos = find_element(nums, target)
    print(' pos: {}'.format(pos))
