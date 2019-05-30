# -*- coding: utf-8 -*-

class Node():

    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


def evaluate_tree(root):
    if root.val.isnumeric():
        return float(root.val)

    lhs = evaluate_tree(root.left)
    rhs = evaluate_tree(root.right)
    if root.val == '+':
        return lhs + rhs
    elif root.val == '-':
        return lhs - rhs
    elif root.val == '*':
        return lhs * rhs
    elif root.val == '/':
        return lhs / rhs

    raise RuntimeError('malformed token:' + root.val)


if __name__ == '__main__':
    root = Node('*')
    root.left = Node('+')
    root.right = Node('+')
    root.left.left = Node('3')
    root.left.right = Node('2')
    root.right.left = Node('4')
    root.right.right = Node('5')

    print('Output: {}'.format(evaluate_tree(root)))
