#include <iostream>

using namespace std;

static const int MAX_LEN = 200;

int bubble_sort(int items[], const int size)
{
  int cnt = 0;
  bool flag = true;
  for (int i = 0; flag; ++i)
    {
      flag = false;
      for (int j = size-1; j >= i + 1; --j)
        {
          if (items[j] < items[j-1])
            {
              swap(items[j], items[j-1]);
              flag = true;
              cnt++;
            }
        }
    }
  return cnt;
}

int main()
{
  int nums[MAX_LEN], n;

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> nums[i];

  int swapCnt = bubble_sort(nums, n);

  for (int i = 0; i < n; ++i)
    {
      if (i > 0) cout << " ";
      cout << nums[i];
    }
  cout << endl;
  cout << swapCnt << endl;

  return 0;
}
