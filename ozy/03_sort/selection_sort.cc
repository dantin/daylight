#include <iostream>

using namespace std;

static const int MAX_LEN = 200;

/**
 * NOT stable
 */
int selection_sort(int items[], const int size)
{
  int cnt = 0;
  for (int i = 0; i < size; ++i)
    {
      int minj = i;
      for (int j = i; j < size; ++j)
        {
          if (items[j] < items[minj]) minj = j;
        }
      int tmp = items[i];
      items[i] = items[minj];
      items[minj] = tmp;
      if (i != minj) cnt++;
    }
  return cnt;
}

int main()
{
  int nums[MAX_LEN], n;

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> nums[i];

  int swapCnt = selection_sort(nums, n);

  for (int i = 0; i < n; ++i)
    {
      if (i > 0) cout << " ";
      cout << nums[i];
    }
  cout << endl;
  cout << swapCnt << endl;

  return 0;
}
