# -*- coding: utf-8 -*-

from math import log


class Solution():

    def crack(self, table):
        transformed_graph = [[-log(edge) for edge in row] for row in table]

        # Pick any source vertex
        # run Bellman-Ford from any vertex and get the right result.
        source = 0
        n = len(transformed_graph)
        min_dist = [float('inf')] * n
        min_dist[source] = 0

        # Relax edges |V - 1| times.
        for _ in range(n - 1):
            for v in range(n):
                for w in range(n):
                    if min_dist[w] > min_dist[v] + transformed_graph[v][w]:
                        min_dist[w] = min_dist[v] + transformed_graph[v][w]

        # If we can still relax edges, then we have a negative cycle.
        for v in range(n):
            for w in range(n):
                if min_dist[w] > min_dist[v] + transformed_graph[v][w]:
                    return True

        return False


if __name__ == '__main__':
    inputs = [
        dict(table=[[1, 2], [2, 1]]),
        dict(table=[[1, 1], [1, 1]]),
    ]

    for i in inputs:
        table = i['table']
        print()
        print(' Input:')
        print('  table:', table)

        solver = Solution()
        can_arbitrage = solver.crack(table)
        print(' Output:', can_arbitrage)
