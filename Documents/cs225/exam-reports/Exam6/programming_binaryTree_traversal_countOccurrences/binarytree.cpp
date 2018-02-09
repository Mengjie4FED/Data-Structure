#define _BINARYTREE_CPP
#include "binarytree.h"
#include <iostream>
#include <cstdlib>

using namespace std;


template <typename T>
int BinaryTree<T>::countOccurrences(const T& elem1) {
  int sum = 0;
  countHelper(elem1, root, sum);
  return sum;
}

template <typename T>
void BinaryTree<T>::countHelper(const T& elem1, Node* subRoot, int & sum){
  if (subRoot == NULL) {return;}

  if (subRoot->elem == elem1 ) {
    sum++;
    countHelper(elem1, subRoot->left, sum);
    countHelper(elem1, subRoot->right, sum);
  } else {
    countHelper(elem1, subRoot->left, sum);
    countHelper(elem1, subRoot->right, sum);
  }
}


/**
 * Constructor to create an empty tree.
 */
template <typename T>
BinaryTree<T>::BinaryTree() : root(NULL) {
  /* nothing */
}

/**
 * Inserts into the BinaryTree, using BST insert algorithm.
 * @param elem The element to insert
 */
template <typename T>
void BinaryTree<T>::insert(const T& elem) {
  insert(root, elem);
}

template <typename T>
void BinaryTree<T>::insert(Node*& node, const T& elem)
{
    // If we're at a NULL pointer, we can put our element here
    if (node == NULL)
        node = new Node(elem);

    // Go left or right
    else if (elem < node->elem)
        insert(node->left, elem);
    else
        insert(node->right, elem);
}
