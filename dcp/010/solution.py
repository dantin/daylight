# -*- coding: utf-8 -*-

import time


def jobscheduler(f, ms):
    time.sleep(ms/1000)
    return f()


if __name__ == '__main__':
    print(time.ctime())
    jobscheduler(lambda: 'Hi ' + time.ctime(), 2000)
    print(time.ctime())
