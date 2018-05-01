#include <iostream>
#include <vector>

using namespace std;

/**
 * Definition for an interval.
 */
struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
  vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
  {
    vector<Interval>::iterator it = intervals.begin();
    while (it != intervals.end()) {
      if (newInterval.end < it->start) {
        intervals.insert(it, newInterval);
        return intervals;
      } else if (newInterval.start > it->end) {
        it++;
        continue;
      } else {
        newInterval.start = min(newInterval.start, it->start);
        newInterval.end = max(newInterval.end, it->end);
        it = intervals.erase(it);
      }
    }
    intervals.insert(intervals.end(), newInterval);

    return intervals;
  }
};

int main()
{
  int s, e;
  int n;

  vector<Interval> intervals;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> s >> e;
    Interval elem(s, e);
    intervals.push_back(elem);
  }
  Interval newInterval;
  cin >> newInterval.start >>newInterval.end;

  Solution sol;
  bool head = true;
  cout << "[";
  for (auto e : sol.insert(intervals, newInterval)) {
    if (!head) cout << ", ";
    cout << "[" << e.start << "," << e.end << "]";
    head = false;
  }
  cout << "]" << endl;

  return 0;
}
