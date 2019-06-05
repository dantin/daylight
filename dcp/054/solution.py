# -*- coding: utf-8 -*-

BOARD_DIM = 9
GRID_DIM = 3


def get_grid_details(x, y):
    grid_row = x - (x % GRID_DIM)
    grid_col = y - (y % GRID_DIM)
    return grid_row, grid_col


def dfs(board, row_elements, col_elements, grid_elements):
    for i in range(BOARD_DIM):
        for j in range(BOARD_DIM):
            if board[i][j] == '.':
                grid_row, grid_col = get_grid_details(i, j)
                grid_key = '{}-{}'.format(grid_row, grid_col)
                for k in range(1, BOARD_DIM + 1):
                    elem = str(k)
                    if ((elem not in row_elements[i]) and 
                            (elem not in col_elements[j]) and
                            (elem not in grid_elements[grid_key])):
                        board[i][j] = elem
                        row_elements[i].add(elem)
                        col_elements[j].add(elem)
                        grid_elements[grid_key].add(elem)
                        if dfs(board, row_elements, col_elements, grid_elements):
                            return True
                        else:
                            board[i][j] = '.'
                            row_elements[i].remove(elem)
                            col_elements[j].remove(elem)
                            grid_elements[grid_key].remove(elem)
                return False
    return True


def solve_sudoku(board):
    row_elements = dict()
    col_elements = dict()
    grid_elements = dict()

    for i in range(BOARD_DIM):
        row_elements[i] = set()
        col_elements[i] = set()

    for i in range(BOARD_DIM):
        for j in range(BOARD_DIM):
            if not i % GRID_DIM and not j % GRID_DIM:
                grid_elements['{}-{}'.format(i, j)] = set()

    for i in range(BOARD_DIM):
        for j in range(BOARD_DIM):
            n = board[i][j]
            if n.isnumeric():
                row_elements[i].add(n)
                col_elements[j].add(n)

                grid_row, grid_col = get_grid_details(i, j)
                grid_elements['{}-{}'.format(grid_row, grid_col)].add(n)

    dfs(board, row_elements, col_elements, grid_elements)


if __name__ == '__main__':
    board = [
        ['5', '3', '.', '.', '7', '.', '.', '.', '.'],
        ['6', '.', '.', '1', '9', '5', '.', '.', '.'],
        ['.', '9', '8', '.', '.', '.', '.', '6', '.'],
        ['8', '.', '.', '.', '6', '.', '.', '.', '3'],
        ['4', '.', '.', '8', '.', '3', '.', '.', '1'],
        ['7', '.', '.', '.', '2', '.', '.', '.', '6'],
        ['.', '6', '.', '.', '.', '.', '2', '8', '.'],
        ['.', '.', '.', '4', '1', '9', '.', '.', '5'],
        ['.', '.', '.', '.', '8', '.', '.', '7', '9']
    ]

    print('original:\n', '\n'.join(' '.join(i) for i in board), sep='')
    solve_sudoku(board)
    print('finished:\n', '\n'.join(' '.join(i) for i in board), sep='')
