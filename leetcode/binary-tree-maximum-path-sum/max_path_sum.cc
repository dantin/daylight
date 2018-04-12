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
  int maxPathSum(TreeNode *root)
  {
    int maxAcrossRoot = INT_MIN;
    int maxEndByRoot = getMax(root, maxAcrossRoot);
    return max(maxAcrossRoot, maxEndByRoot);
  }

  int getMax(TreeNode *node, int &maxAcrossRoot)
  {
    if (node == NULL) return 0;
    int left = getMax(node->left, maxAcrossRoot);
    int right = getMax(node->right, maxAcrossRoot);
    int cMax = node->val;
    if (left > 0) {
      cMax += left;
    }
    if (right > 0) {
      cMax += right;
    }
    maxAcrossRoot = max(maxAcrossRoot, cMax);
    return max(node->val,
               max(node->val+left, node->val+right));
  }
};

int main()
{
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);

  Solution s;
  cout << s.maxPathSum(root) << endl;

  return 0;
}
