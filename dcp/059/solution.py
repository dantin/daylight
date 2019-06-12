# -*- coding: utf-8 -*-

import hashlib


m = hashlib.md5


class MerkleNode():

    def __init__(self):
        self.parent = None
        self.node_hash = None


class MerkleDirectory(MerkleNode):

    def __init__(self):
        MerkleNode.__init__(self)
        self.children = []
        self.is_dir = True

    def recalculate_hash(self):
        if self.children:
            collated_hash = ''
            for child in self.children:
                collated_hash += child.node_hash
            self.node_hash = m(collated_hash.encode()).hexdigest()


class MerkleFile(MerkleNode):

    def __init__(self):
        MerkleNode.__init__(self)
        self.node_contents = None
        self.is_dir = False

    def update_contents(self, contents):
        self.node_hash = m(contents.encode()).hexdigest()
        self.node_contents = contents
        if self.parent:
            self.parent.recalculate_hash()

    def add_to_directory(self, dir_node):
        self.parent = dir_node
        dir_node.children.append(self)

        while dir_node:
            dir_node.recalculate_hash()
            dir_node = dir_node.parent


if __name__ == '__main__':
    a_1 = MerkleFile()
    b_1 = MerkleDirectory()
    a_1.update_contents('abc')
    a_1.add_to_directory(b_1)

    print(b_1.node_hash)

    a_2 = MerkleFile()
    b_2 = MerkleDirectory()
    a_2.update_contents('abc')
    a_2.add_to_directory(b_2)

    print(b_2.node_hash)
