#include <iostream>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  bool isBalanced(TreeNode *root)
  {
    if (root == NULL) return true;
    int val = getBalance(root);
    if (val == -1) return false;
    return true;
  }

  int getBalance(TreeNode *node)
  {
    if (node == NULL) return 0;
    int left = getBalance(node->left);
    if (left == -1) return -1;
    int right = getBalance(node->right);
    if (right == -1) return -1;
    if (left - right > 1 || right - left > 1) {
      return -1;
    }
    return left > right ? left + 1 : right + 1;
  }
};

int main()
{
  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(9);
  root->right = new TreeNode(20);
  root->right->left = new TreeNode(15);
  root->right->right = new TreeNode(7);

  Solution s;
  cout << s.isBalanced(root) << endl;

  return 0;
}
