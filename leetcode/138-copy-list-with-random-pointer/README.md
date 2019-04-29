Copy List with Random Pointer
---

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a _deep copy_ of the list.

__Example 1__:

```
Input:
{"$id":"1","next":{"$id":"2","next":null,"random":{"$ref":"2"},"val":2},"random":{"$ref":"2"},"val":1}

Explanation:
Node 1's value is 1, both of its next and random pointer points to Node 2.
Node 2's value is 2, its next pointer points to null and its random pointer points to itself.
```

__Note__:

1. You must return the __copy of the given head__ as a reference to the cloned list.
