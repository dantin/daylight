#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  TreeNode *sortedListToBST(ListNode *head) {
    int len = 0;
    ListNode *p = head;
    while (p) {
      len++;
      p = p->next;
    }
    return buildBST(head, 0, len-1);
  }

  TreeNode *buildBST(ListNode *&list, int start, int end)
  {
    if (start > end) return NULL;
    int mid = (start+end)/2;
    TreeNode *leftChild = buildBST(list, start, mid-1);
    TreeNode *parent = new TreeNode(list->val);
    parent->left = leftChild;
    list = list->next;
    parent->right = buildBST(list, mid+1, end);
    return parent;
  }
};

/*
void traversal(ListNode *p)
{
  bool head = true;
  while(p) {
    if (!head) cout << " -> ";
    cout << p->val;
    p = p->next;
    head = false;
  }
  cout << endl;
}
*/

int main()
{
  ListNode *head, *tail;
  int n;

  head = new ListNode(-1);
  tail = head;

  while(cin >> n) {
    ListNode *node = new ListNode(n);
    tail->next = node;
    tail = tail->next;
  }
  tail = head;
  head = head->next;
  delete tail;
  tail = NULL;
  //traversal(head);

  Solution s;
  TreeNode *root = s.sortedListToBST(head);

  return 0;
}
