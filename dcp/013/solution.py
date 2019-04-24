# -*- coding: utf-8 -*-

class Solution():

    def crack(self, s, k):
        pos, slow, count = 0, 0, 0
        cache = {}
        for fast in range(len(s)):
            c = s[fast]
            if c in cache:
                cache[c] += 1
            else:
                cache[c] = 1

            if len(cache) > k:
                count = max(count, fast - slow)
                if count == fast - slow:
                    pos = slow

                while len(cache) > k:
                    t = s[slow]
                    if cache[t] > 1:
                        cache[t] -= 1
                    else:
                        del cache[t]
                    slow += 1

        window = max(count, len(s) - slow)
        return s[pos:pos + window]


if __name__ == '__main__':
    inputs = [
        dict(s='abcba', k=2),
        dict(s='aabacbebebe', k=3),
    ]

    for i in inputs:
        s, k = i['s'], i['k']
        print(' Input: s={}, k={}'.format(s, k))

        solver = Solution()
        count = solver.crack(s, k)
        print(' Output:', count)
