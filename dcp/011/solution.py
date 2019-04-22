# -*- coding: utf-8 -*-

class TrieNode():

    def __init__(self):
        self.children = {}
        self.last = False


class Trie():

    def __init__(self):
        self.root = TrieNode()
        self.word_list = []

    def build(self, terms):
        for term in terms:
            self.insert(term)

    def insert(self, term):
        node = self.root

        for c in list(term):
            if not node.children.get(c):
                node.children[c] = TrieNode()
            node = node.children[c]

        node.last = True

    def search(self, query):
        node = self.root
        found = True

        for c in list(query):
            if not node.children.get(c):
                found = False
                break
            node = node.children[c]

        return found, node


class Solution():

    def __init__(self, terms):
        self.trie = Trie()
        self.trie.build(terms)

    def crack(self, query):
        found, node = self.trie.search(query)
        if (not found) or node.last:
            return []

        suggestions = []
        self.fill_suggesttions(suggestions, node, query)

        return suggestions

    def fill_suggesttions(self, suggestions, node, word):
        if node.last:
            suggestions.append(word)

        for c, n in node.children.items():
            self.fill_suggesttions(suggestions, n, word + c)


if __name__ == '__main__':
    inputs = [
        dict(keys=['dog', 'deer', 'deal'], target='de'),
    ]

    for i in inputs:
        keys, target = i['keys'], i['target']

        print(' Input:')
        print('  Terms:', keys)
        print('  Query:', target)

        solver = Solution(keys)

        suggestions = solver.crack(target)
        print(' Output:', ', '.join(suggestions))
