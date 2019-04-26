# -*- coding: utf-8 -*-

class OrdersLog():

    def __init__(self, size):
        self.buffer = [None] * size
        self.idx = 0

    def record(self, order_id):
        self.buffer[self.idx] = order_id
        self.idx = (self.idx + 1) % len(self.buffer)

    def get_last(self, i):
        return self.buffer[(self.idx - i + len(self.buffer)) % len(self.buffer)]


if __name__ == '__main__':
    log = OrdersLog(10)
    for i in range(15):
        log.record(i)
    print(log.get_last(3))
