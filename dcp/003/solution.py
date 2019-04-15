# -*- coding: utf-8 -*-


class Node():
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution():

    def deserialize(self, data):

        def decode(vals):
            val = next(vals)
            if val == '#':
                return None

            node = Node(val)
            node.left = decode(vals)
            node.right = decode(vals)
            return node

        vals = iter(data.split())
        return decode(vals)

    def serialize(self, root):
        vals = []

        def encode(node):
            if node:
                vals.append(str(node.val))
                encode(node.left)
                encode(node.right)
            else:
                vals.append('#')

        encode(root)

        return ' '.join(vals)


if __name__ == '__main__':
    node = Node('root', Node('left', Node('left.left')), Node('right'))
    solver = Solution()
    assert solver.deserialize(solver.serialize(node)).left.left.val == 'left.left'
