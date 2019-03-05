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
    vector<TreeNode *> sta;
    vector<int> result;

    if (root == NULL) return result;
    TreeNode *node = root;
    while (sta.size() > 0 || node != NULL) {
      while (node != NULL) {
        sta.push_back(node);
        node = node->left;
      }
      node = sta.back();
      sta.pop_back();
      result.push_back(node->val);
      node = node->right;
    }
    return result;
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
