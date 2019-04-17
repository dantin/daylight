# -*- coding: utf-8 -*-


class XORLinkedListNode():

    def __init__(self, val, prev_idx, next_idx):
        self.val = val
        self.both = prev_idx ^ next_idx

    def next_node(self, prev_idx):
        return self.both ^ prev_idx

    def prev_node(self, next_idx):
        return self.both ^ next_idx


class XORLinkedList():
    
    def __init__(self):
        self.memory = [XORLinkedListNode(None, -1, -1)]

    def head(self):
        """head node index, prev node index, and node"""
        return 0, -1, self.memory[0]

    def add(self, val):
        curr_idx, prev_idx, curr_node = self.head()
        while True:
            next_idx = curr_node.next_node(prev_idx)
            if next_idx == -1:
                break
            prev_idx, curr_idx = curr_idx, next_idx
            curr_node = self.memory[next_idx]

        new_idx = len(self.memory)
        curr_node.both = prev_idx ^ new_idx
        self.memory.append(XORLinkedListNode(val, curr_idx, -1))

    def get(self, idx):
        curr_idx, prev_idx, curr_node = self.head()
        for i in range(idx + 1):
            prev_idx, curr_idx = curr_idx, curr_node.next_node(prev_idx)
            curr_node = self.memory[curr_idx]
        return curr_node.val


if __name__ == '__main__':
    nums = XORLinkedList()

    for i in range(3):
        nums.add(i)
    for i in range(3):
        print('nums[{}] = {}'.format(i, nums.get(i)))
