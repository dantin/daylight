# -*- coding: utf-8 -*-

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def addTwoNumbers(self, li: ListNode, l2: ListNode) -> ListNode:
        return []


def make_num(num:str) -> ListNode:
    head, tail = None, None
    for c in num:
        curr_node = ListNode(int(c))
        if head is None:
            head = curr_node
            tail = curr_node
        else:
            tail.next = curr_node
            tail = curr_node
            
    return head

def print_nums(node: ListNode):
    nums = []
    while node is not None:
        nums.append(chr(ord('0') + node.val))
        node = node.next
    print(' -> '.join(nums))


if __name__ == '__main__':
    num1 = make_num('360')
    print_nums(num1)

