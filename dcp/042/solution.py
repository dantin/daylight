# -*- coding: utf-8 -*-

class Solution():

    def crack(self, data, target):
        def dfs(depth, start, values):
            if sum(values) == target:
                res.append(list(values))
            if depth == len(data):
                return
            for i in range(start, len(data)):
                dfs(depth + 1, i + 1, values + [data[i]])

        data.sort()
        res = []
        dfs(0, 0, [])
        return res


if __name__ == '__main__':
    inputs = [
        dict(data=[12, 1, 61, 5, 9, 2], k=24),
        dict(data=[12, 1, 61, 5, 9, 2], k=61),
        dict(data=[12, 1, 61, -108, 2], k=-106),
    ]

    for i in inputs:
        data, k = i['data'], i['k']
        print('\n Input:')
        print('  S: {}'.format(data))
        print('  k = {}'.format(k))

        solver = Solution()
        ans = solver.crack(data, k)
        print(' Output:', ans)
