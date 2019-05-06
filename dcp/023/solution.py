# -*- coding: utf-8 -*-

class Solution():

    def crack(self, matrix, start, end):
        coords = [(r, c) for r, row in enumerate(matrix)
                  for c, elem in enumerate(row) if not elem]
        rows, cols = len(matrix), len(matrix[0])
        distances = [[None for col in range(cols)] for _ in range(rows)]
        distances[start[0]][start[1]] = 0
        current_distance = 0
        
        while True:
            wavefront = [coord for coord in coords if distances[coord[0]][coord[1]] == current_distance]
            if not wavefront:
                break

            current_distance += 1
            for node in wavefront:
                neighbours = [coord for coord in coords if (abs(node[0] - coord[0]) + abs(node[1] - coord[1])) == 1]
                for n in neighbours:
                    if distances[n[0]][n[1]] is None:
                        distances[n[0]][n[1]] = current_distance

        return distances[end[0]][end[1]]


if __name__ == '__main__':
    inputs = [
        dict(matrix=[
            [False, False, False, False],
            [True, True, False, True],
            [False, False, False, False],
            [False, False, False, False],
            ],
            start=(3, 0),
            end=(0, 0)),
    ]

    for i in inputs:
        matrix, start, end = i['matrix'], i['start'], i['end']
        print(' Input:\n  matrix = {}'.format(matrix))
        print('  start  = {}'.format(start))
        print('  end    = {}'.format(end))

        solver = Solution()
        length = solver.crack(matrix, start, end)
        print(' Output: {}'.format(length))
