// version 1.0 2018-05-29
#include <iostream>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    bool hasCycle(ListNode *head)
    {
      if (head == NULL) return false;
      ListNode *first  = head;
      ListNode *second = head->next;
      while (first != NULL && second != NULL) {
        if (first == second) return true;
        first = first->next;
        second = second->next;
        if (second == NULL) {
          return false;
        }
        second = second->next;
      }
      return false;
    }
};

int main()
{
  ListNode *head = NULL, *tail = NULL, *p;
  int n, v;

  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> v;
    p = new ListNode(v);
    if (head == NULL) {
      tail = p;
      head = tail;
    } else {
      tail->next = p;
      tail = p;
    }
  }
  tail->next = head;

  Solution s;
  cout << s.hasCycle(head) << endl;

  return 0;
}
