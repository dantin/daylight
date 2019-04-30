# -*- coding: utf-8 -*-


class LinkedListNode():

    def __init__(self, value, next_node=None):
        self.value = value
        self.next_node = next_node


def len_list(node):
    size = 0
    while node is not None:
        size += 1
        node = node.next_node
    return size


def print_list(node):
    sep = ''
    while node is not None:
        print('{}{}'.format(sep, node.value), end='')
        sep = ' -> '
        node = node.next_node


class Solution():

    def crack(self, lhs, rhs):
        if (lhs is None) or (rhs is None):
            return None

        lhs_size = len_list(lhs)
        rhs_size = len_list(rhs)

        p1, p2 = lhs, rhs
        if lhs_size > rhs_size:
            diff = lhs_size - rhs_size
            for _ in range(diff):
                p1 = p1.next_node
        else:
            diff = rhs_size - lhs_size
            for _ in range(diff):
                p2 = p2.next_node

        while (p1 is not None) and (p2 is not None):
            if p1.value == p2.value:
                return p1
            p1 = p1.next_node
            p2 = p2.next_node

        return None
            

if __name__ == '__main__':
    n1 = LinkedListNode(3)
    n2 = LinkedListNode(7)
    n3 = LinkedListNode(99)
    n4 = LinkedListNode(1)
    n5 = LinkedListNode(8)
    n6 = LinkedListNode(10)

    n1.next_node = n2
    n2.next_node = n5
    n5.next_node = n6
    n3.next_node = n4
    n4.next_node = n5

    A, B = n1, n3
    print(' Input:')
    print('\n  A = ', end='')
    print_list(A)
    print('\n  B = ', end='')
    print_list(B)
    print()

    solver = Solution()
    node = solver.crack(A, B)
    print(' Output:', node.value)
