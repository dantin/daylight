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
  TreeNode *flatten(TreeNode *root)
  {
    if (root == NULL) return NULL;
    TreeNode *rightTree = root->right;
    TreeNode *newHead = root;
    TreeNode *leftList = flatten(root->left);
    if (leftList != NULL) {
      newHead = leftList;
      TreeNode *tail = leftList->left;
      tail->right = root;
      root->left = tail;
      leftList->left = root;
    }
    TreeNode *rightList = flatten(rightTree);
    if (rightList != NULL) {
      root->right = rightList;
      newHead->left = rightList->left;
      rightList->left = root;
    }
    return newHead;
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
