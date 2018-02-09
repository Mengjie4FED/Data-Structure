#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class BinaryTree {
  private:
    struct Node {
        T elem;
        Node* left;
        Node* right;
        Node(const T& element) : elem(element), left(NULL), right(NULL) { }
    };

    Node* root;
    void insert(Node*& node, const T& elem);

  public:
    BinaryTree();
    int countOccurrences(const T& elem1);
    void insert(const T& elem);
    int countHelper(const T& elem1, Node* subRoot, int sum);
};

#ifndef _BINARYTREE_CPP
#include "binarytree.cpp"
#endif

#endif
