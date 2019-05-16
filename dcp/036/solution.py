# -*- coding: utf-8 -*-

import heapq as hq


class Node():

    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


def travel(node, path):
    if node is None:
        return

    travel(node.left, path)
    travel(node.right, path)

    hq.heappush(path, node.val)


class Solution():

    def crack(self, root):
        path = []
        travel(root, path)
        return min(path[-2:])


if __name__ == '__main__':
    root = Node(3)
    root.left = Node(1)
    root.right = Node(4)
    root.left.left = Node(7)

    solver = Solution()
    second_largest = solver.crack(root)
    print(second_largest)
