# -*- coding: utf-8 -*-

class Solution():

    def encode(self, raw):
        count, prev = 1, ''
        encoded = ''
        for c in raw:
            if c != prev:
                if prev:
                    encoded += str(count) + prev
                count, prev = 1, c
            else:
                count += 1
        if prev:
            encoded += str(count) + prev

        return encoded 

    def decode(self, encoded):
        data = ''
        while encoded:
            count, c, *encoded = encoded
            data += c * int(count)
        
        return data


if __name__ == '__main__':
    inputs = [
        'AAAABBBCCDAA'
    ]

    for s in inputs:
        print()
        print(' Input:', s)

        solver = Solution()
        encoded = solver.encode(s)
        print(' Output:')
        print('  encoded:  ', encoded)
        orig = solver.decode(encoded)
        print('  original: ', orig)
