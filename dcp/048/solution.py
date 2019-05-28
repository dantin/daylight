# -*- coding: utf-8 -*-


class Node():

    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


def make_tree(preorder, inorder):
    if not preorder or not inorder:
        return None

    root_val = preorder[0]
    if len(preorder) == 1:
        return Node(root_val)

    root_node = Node(root_val)
    for i, val in enumerate(inorder):
        if val == root_val:
            root_node.left = make_tree(
                preorder=preorder[1:i+1], inorder=inorder[:i])
            root_node.right = make_tree(
                preorder=preorder[i+1:], inorder=inorder[i+1:])

    return root_node


def print_tree(node, path):
    if not node:
        return
    path.append('\'{}\''.format(node.val))
    print_tree(node.left, path)
    print_tree(node.right, path)


if __name__ == '__main__':
    inputs = (
        dict(preorder=['a', 'b', 'd', 'e', 'c', 'f', 'g'],
            inorder=['d', 'b', 'e', 'a', 'f', 'c', 'g']),
    )

    for elem in inputs:
        preorder, inorder = elem['preorder'], elem['inorder']
        print('\n Input:')
        print('  preorder: {}'.format(preorder))
        print('  inorder: {}'.format(inorder))

        root = make_tree(preorder, inorder)

        path = []
        print_tree(root, path)
        print(' Output:')
        print('  inorder: {}'.format(', '.join(path)))
