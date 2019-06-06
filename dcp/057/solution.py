# -*- coding: utf-8 -*-

def break_text(sentence, k):
    words = sentence.split()

    broken_text = []
    char_count = -1
    current_words = []
    idx = 0
    while idx < len(words):
        word = words[idx]

        if len(word) > k:
            return None

        if char_count + len(word) + 1 <= k:
            char_count += len(word) + 1
            current_words.append(word)
            idx += 1
        else:
            broken_text.append(' '.join(current_words))
            char_count = -1
            current_words = []
    broken_text.extend(current_words)

    return broken_text


if __name__ == '__main__':
    sentence = 'the quick brown fox jumps over the lazy dog'
    k = 10
    print(' Input:', sentence)
    print(' k:', k)
    texts = break_text(sentence, k)
    print(' Output:')
    print('\n'.join(texts))
