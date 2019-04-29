# -*- coding: utf-8 -*-

class Solution():

    def crack(self, costs):
        if (costs is None) or (not costs):
            return 0

        n, k = len(costs), len(costs[0])
        prev, curr = costs[0], []
        for i in range(1, n):
            for j in range(k):
                curr.append(min(prev[m] + costs[i][j] for m in range(k) if m != j))
            prev, curr = curr, []
        
        return min(prev[i] for i in range(k))


if __name__ == '__main__':
    costs = [
        [8, 3, 2],
        [4, 5, 1],
    ]
    solver = Solution()
    cost = solver.crack(costs)
    print(cost)
