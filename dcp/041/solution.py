# -*- coding: utf-8 -*-

class Solution():

    def crack(self, flights, start_point):
        itinerary = []
        return self.dfs(flights, start_point, itinerary)

    def dfs(self, flights, start_point, current_itinerary):
        if not flights:
            return current_itinerary + [start_point]

        updated_itinerary = None
        for idx, (source, destination) in enumerate(flights):
            if start_point == source:
                child_itinerary = self.dfs(
                    flights[:idx] + flights[idx + 1:], destination, current_itinerary + [source])
                if child_itinerary:
                    if not updated_itinerary or ''.join(child_itinerary) < ''.join(updated_itinerary):
                        updated_itinerary = child_itinerary

        return updated_itinerary


if __name__ == '__main__':
    inputs = [
        dict(flights=[('SFO', 'HKO'), ('YYZ', 'SFO'), ('YUL', 'YYZ'),
            ('HKO', 'ORD')], start_point='YUL'),
        dict(flights=[('SFO', 'COM'), ('COM', 'YYZ')], start_point='YUL'),
        dict(flights=[('A', 'B'), ('A', 'C'), ('B', 'C'), ('C', 'A')],
            start_point='A'),
    ]

    for i in inputs:
        flights, start_point = i['flights'], i['start_point']
        print('\n Input:')
        print('  flights: {}'.format(flights))
        print('  start_point: \'{}\''.format(start_point))

        solver = Solution()
        path = solver.crack(flights, start_point)
        print(' Output: {}'.format(path))
