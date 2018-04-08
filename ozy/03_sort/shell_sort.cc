#include <iostream>
#include <vector>

using namespace std;

const static int MAX_LEN = 200;

int cnt;
vector<int> G;

void insert_sort(int items[], const int size, const int g)
{
  for (int i = g; i < size; ++i) {
    int v = items[i];
    int j = i-g;
    while (j >= 0 && items[j] > v) {
      items[j+g] = items[j];
      j -= g;
      cnt++;
    }
    items[j+g] = v;
  }
}

void shell_sort(int items[], const int size)
{
  for (int h = 1;;) {
    if (h > size) break;
    G.push_back(h);
    h = 3*h + 1;
  }

  for (int i = G.size()-1; i >= 0; --i) {
    insert_sort(items, size, G[i]);
  }
}

int main()
{
  int nums[MAX_LEN];
  int n;

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> nums[i];

  shell_sort(nums, n);

  cout << G.size() << endl;
  for (int i = G.size()-1; i >= 0; --i) {
    cout << G[i];
    if (i > 0) cout << " ";
  }
  cout << endl;

  cout << cnt << endl;
  for (int i = 0; i < n; ++i) cout << nums[i] << endl;

  return 0;
}
