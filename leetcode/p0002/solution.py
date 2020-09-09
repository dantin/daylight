# -*- coding: utf-8 -*-

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        head, tail = None, None
        s = 0
        while (l1 is not None) or (l2 is not None) or (s != 0):
            if l1 is not None:
                s += l1.val
                l1 = l1.next
            if l2 is not None:
                s += l2.val
                l2 = l2.next
            curr_node = ListNode(s % 10)
            s //= 10
            if head is None:
                head = curr_node
                tail = curr_node
            else:
                tail.next = curr_node
                tail = curr_node

        return head 


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
    num1 = make_num('342')
    num2 = make_num('465')
    s = Solution()

    res = s.addTwoNumbers(num1, num2)

    print_nums(num1)
    print_nums(num2)
    print_nums(res)

