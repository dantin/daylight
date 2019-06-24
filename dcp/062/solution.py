# -*- coding: utf-8 -*-

def dfs(rows, cols, curr_row, curr_col):
    if curr_row == rows - 1 and curr_col == cols - 1:
        return 1

    count = 0
    if curr_row < rows - 1:
        count += dfs(rows, cols, curr_row + 1, curr_col)
    if curr_col < cols - 1:
        count += dfs(rows, cols, curr_row, curr_col + 1)

    return count


def matrix_traversals_count(rows, cols):
    if not rows or not cols:
        return None
    count = dfs(rows, cols, 0, 0)
    return count


if __name__ == '__main__':
    inputs = [
        (5, 5),
    ]

    for rows, cols in inputs:
        print('\n Input:')
        print(' rows = {}, cols = {}'.format(rows, cols))
        count = matrix_traversals_count(rows, cols)
        print(' Output: {}'.format(count))
