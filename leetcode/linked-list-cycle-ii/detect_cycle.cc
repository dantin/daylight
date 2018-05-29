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
    ListNode *detectCycle(ListNode *head)
    {
      ListNode *first = head;
      ListNode *second = head;

      while (first != NULL && second != NULL) {
        first = first->next;
        second = second->next;
        if (second != NULL) {
          second = second->next;
        }
        if (first == second) {
          break;
        }
      }
      if (second == NULL) return NULL;

      // move another X steps to find the head
      first = head;
      while (first != second) {
        first = first->next;
        second = second->next;
      }
      return second;
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
  cout << s.detectCycle(head)->val << endl;

  return 0;
}
