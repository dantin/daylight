#include <iostream>

using namespace std;

static const int MAX_LEN = 200;


void trace(int items[], const int size)
{
  for (int i = 0; i < size; ++i)
    {
      if (i > 0) cout << " ";
      cout << items[i];
    }
  cout << endl;
}

void insert_sort(int items[], const int size)
{
  for (int i = 1; i < size; ++i)
    {
      int v = items[i];
      int j = i-1;
      while (j >= 0 && items[j] > v)
        {
          items[j+1] = items[j];
          j--;
        }
      items[j+1] = v;
      trace(items, size);
    }
}

int main()
{
  int n;
  int nums[MAX_LEN];

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> nums[i];

  trace(nums, n);
  insert_sort(nums, n);

  return 0;
}
