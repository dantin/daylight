# -*- coding: utf-8 -*-

class ListNode():

    def __init__(self, val, next_node=None):
        self.val = val
        self.next_node = next_node


class Solution():

    def crack(self, head, n):
        fast, slow = head, head

        count = 0
        while count < n:
            fast = fast.next_node
            count += 1

        if fast is None:
            head = head.next_node
            return head

        while fast is not None:
            fast = fast.next_node
            slow = slow.next_node

        slow.next_node = slow.next_node.next_node

        return head


def make_list(nums):
    dummy = ListNode(None)
    prev = dummy
    for i in nums:
        node = ListNode(i)
        prev.next_node = node
        prev = node

    return dummy.next_node


def print_list(node):
    s = ''
    while node is not None:
        print('{}{}'.format(s, node.val), end='')
        node = node.next_node
        s = ' -> '
    print()


if __name__ == '__main__':
    inputs = [
        dict(nums=[1, 2, 3, 4], k=3),
        dict(nums=[1, 2, 3], k=3),
    ]

    for i in inputs:
        nums, k = i['nums'], i['k']
        head = make_list(nums)
        print(' Input: k = {}, nums = '.format(k), end='')
        print_list(head)

        solver = Solution()
        head = solver.crack(head, k)
        print(' Output: ', end='')
        print_list(head)
        print()
