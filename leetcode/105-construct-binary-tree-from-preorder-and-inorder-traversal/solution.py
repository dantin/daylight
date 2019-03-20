# -*- coding: utf-8 -*-

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def buildTree(self, preorder, inorder):
        if len(preorder) != len(inorder):
            return None

        return dfs(preorder, 0, len(preorder) - 1, inorder, 0, len(inorder) - 1)


def dfs(preorder, pre_low, pre_high, inorder, in_low, in_high):
    if pre_low > pre_high:
        return None

    pivot = preorder[in_low]
    i = pre_low
    while i < pre_high:
        if inorder[i] == pivot:
            break
        i += 1

    node = TreeNode(pivot)
    node.left = dfs(preorder, pre_low, i - 1, inorder, in_low + 1, i - pre_low + in_low)
    node.right = dfs(preorder, i + 1, pre_high, inorder, i - pre_low + in_low + 1, in_high)

    return node


def print_tree(node):
    if node is None:
        print('# ', end='')
        return
    print(node.val, '', end='')
    print_tree(node.left)
    print_tree(node.right)


if __name__ == '__main__':
    preorder = [3, 9, 20, 15, 7]
    inorder = [9, 3, 15, 20, 7]
    print('', 'Input:')
    print(' ', 'preorder: ', preorder)
    print(' ', 'inorder:', inorder)
    solution = Solution()
    root = solution.buildTree(preorder, inorder)
    print('', 'Output:')
    print('  ', end='')
    print_tree(root)
    print()
