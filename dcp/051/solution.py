# -*- coding: utf-8 -*-

import random


def random_num(k):
    return random.randint(0, k)


def shuffle_card(cards_size=52):
    cards = [x for x in range(cards_size)]

    for i in cards:
        pos = i + random_num(cards_size - i - 1)
        cards[i], cards[pos] = cards[pos], cards[i]

    return cards


if __name__ == '__main__':
    print('shuffle:', shuffle_card())
