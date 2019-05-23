# -*- coding: utf-8 -*-

class Stack():
    
    def __init__(self):
        self.stack = []
        self.max_stack = []

    def push(self, val):
        self.stack.append(val)
        if not self.max_stack or val > self.stack[self.max_stack[-1]]:
            self.max_stack.append(len(self.stack) - 1)

    def pop(self, val):
        if not self.stack:
            return None
        if len(self.stack) - 1 == self.max_stack[-1]:
            self.max_stack.pop()

        return self.stack.pop()

    def max(self):
        if not self.stack:
            return None
        return self.stack[self.max_stack[-1]]


if __name__ == '__main__':
    inputs = [
        [ 1, 3, 4, 5 ]
    ]

    for data in inputs:
        print('\n data: {}'.format(data))
        stack = Stack()
        for i in data:
            stack.push(i)
        print(' max: {}'.format(stack.max()))
