# -*- coding: utf-8 -*-


class Node():

    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


class Solution():

    def __init__(self):
        self.count = 0

    def crack(self, root):
        self.count = 0
        self.count_single(root)
        return self.count

    def count_single(self, node):
        if node is None:
            return True

        left = self.count_single(node.left)
        right = self.count_single(node.right)

        if (not left) or (not right):
            return False

        if node.left and node.val != node.left.val:
            return False

        if node.right and node.val != node.right.val:
            return False

        self.count += 1
        return True


def build_tree(nums):
    if (nums is None) or (not nums):
        return None

    def build_tree_node(nums, idx):
        if (idx >= len(nums)) or (nums[idx] is None):
            return None

        left, right = idx * 2 + 1, idx * 2 + 2

        node = Node(nums[idx])
        node.left = build_tree_node(nums, left)
        node.right = build_tree_node(nums, right)

        return node

    return build_tree_node(nums, 0)


def print_tree(node, path):
    if node is None:
        path.append('#')
        return

    path.append(str(node.val))
    print_tree(node.left, path)
    print_tree(node.right, path)


if __name__ == '__main__':
    inputs = [
        [0, 1, 0, None, None, 1, 0, None, None, None, None, 1, 1],
    ]

    for nums in inputs:
        root = build_tree(nums)

        path = []
        print_tree(root, path)
        print(' Input:', ', '.join(path))

        sovler = Solution()
        cnt = sovler.crack(root)
        print(' Output:', cnt)
