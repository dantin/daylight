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
  TreeNode *flattenT(TreeNode *root)
  {
    if (!root ||
        (!root->left && !root->right)) {
      return root;
    }
    TreeNode *node1 = flattenT(root->left),
             *node2 = flattenT(root->right);
    
    if (node1) node1->right = root->right;
    if (root->left) root->right = root->left;
    root->left = NULL;

    return (node2) ? node2 : node1;
  }

  void flatten(TreeNode *root)
  {
    flattenT(root);
  }
};

int main() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(5);
  root->left->left = new TreeNode(3);
  root->left->right = new TreeNode(4);
  root->right->right = new TreeNode(6);

  Solution s;
  s.flatten(root);

  return 0;
}
