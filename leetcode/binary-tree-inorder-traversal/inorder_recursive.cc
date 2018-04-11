#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  vector<int> inorderTraversal(TreeNode *root)
  {
    vector<int> result;
    inorderTra(root, result);
    return result;
  }

  void inorderTra(TreeNode *node, vector<int> &result)
  {
    if (node == NULL) {
      return;
    }
    inorderTra(node->left, result);
    result.push_back(node->val);
    inorderTra(node->right, result);
  }
};

int main()
{
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);

  Solution s;
  vector<int> inorder = s.inorderTraversal(root);

  bool head = true;
  for (auto i : inorder) {
    if (!head) cout << ", ";
    cout << i;
    head = false;
  }
  cout << endl;

  return 0;
}
