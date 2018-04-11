#include <vector>
#include <iostream>
#include <queue>

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
  vector<vector<int>> levelOrder(TreeNode *root)
  {
    vector<vector<int>> result;

    if (root == NULL) return result;
    queue<TreeNode *> nodeQ;
    nodeQ.push(root);
    int nextLevelCnt = 0, currentLevelCnt = 1;
    vector<int> layer;
    int visitedCnt = 0;
    while (nodeQ.size() != 0) {
      TreeNode *node = nodeQ.front();
      nodeQ.pop();
      visitedCnt++;
      layer.push_back(node->val);
      if (node->left != NULL) {
        nodeQ.push(node->left);
        nextLevelCnt++;
      }
      if (node->right != NULL) {
        nodeQ.push(node->right);
        nextLevelCnt++;
      }
      if (visitedCnt == currentLevelCnt) {
        visitedCnt = 0;
        currentLevelCnt = nextLevelCnt;
        nextLevelCnt = 0;
        result.push_back(layer);
        layer.clear();
      }
    }
    return result;
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
  vector<vector<int>> levels = s.levelOrder(root);

  for (auto level : levels) {
    cout << "[ ";
    bool head = true;
    for (auto n : level) {
      if (!head) cout << ", ";
      cout << n;
      head = false;
    }
    cout << " ]" << endl;
  }
  return 0;
}
