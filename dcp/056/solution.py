# -*- coding: utf-8 -*-

def can_color_graph(adjacency_matrix, k):
    max_adjacencies = 0
    for row in adjacency_matrix:
        max_adjacencies = max(max_adjacencies, sum(row))

    return k > max_adjacencies


if __name__ == '__main__':
    graph = [
        [0, 1, 1, 1],
        [1, 0, 1, 1],
        [1, 1, 0, 1],
        [1, 1, 1, 0],
    ]
    print('\ngraph:')
    print('\n'.join(', '.join(str(j) for j in i) for i in graph))
    k = 3
    print('k = {}'.format(k))
    ans = can_color_graph(graph, k)
    print('ans: {}'.format(ans))
