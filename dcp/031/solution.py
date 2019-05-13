# -*- coding: utf-8 -*-

def edit_distance(word1, word2):
    if word1 == word2:
        return 0
    elif not word1:
        return len(word2)
    elif not word2:
        return len(word1)

    if word1[0] == word2[0]:
        return edit_distance(word1[1:], word2[1:])

    return 1 + min(
            edit_distance(word1[1:], word2),
            edit_distance(word1, word2[1:]),
            edit_distance(word1[1:], word2[1:]))


if __name__ == '__main__':
    inputs = [
        dict(word1='kitten', word2='sitting'),
    ]

    for i in inputs:
        word1, word2 = i['word1'], i['word2']
        print(' Input:')
        print('  word1:', word1)
        print('  word2:', word2)

        distance = edit_distance(word1, word2)
        print(' Output:', distance)
