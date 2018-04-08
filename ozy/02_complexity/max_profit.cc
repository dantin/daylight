#include <iostream>
#include <algorithm>

using namespace std;

static const int MAX = 200000;

int main()
{
  int R[MAX], n;

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> R[i];

  int maxP = INT_MIN;
  int minV = R[0];

  for (int i = 1; i < n; ++i)
    {
      maxP = max(maxP, R[i]-minV);
      minV = min(minV, R[i]);
    }

  cout << maxP << endl;

  return 0;
}
