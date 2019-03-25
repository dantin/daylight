#include <vector>
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  TreeNode *sortedArrayToBST(vector<int> &num)
  {
    return buildTree(num, 0, num.size()-1);
  }

  TreeNode *buildTree(vector<int> &num, int start, int end)
  {
    if (start > end) return NULL;
    if (start == end) return new TreeNode(num[start]);
    int mid = (start+end)/2;
    TreeNode *node = new TreeNode(num[mid]);
    node->left = buildTree(num, start, mid-1);
    node->right = buildTree(num, mid+1, end);
    return node;
  }
};

int main()
{
  vector<int> nums;
  int n;

  while (cin >> n) nums.push_back(n);

  Solution s;
  TreeNode *root = s.sortedArrayToBST(nums);

  return 0;
}
