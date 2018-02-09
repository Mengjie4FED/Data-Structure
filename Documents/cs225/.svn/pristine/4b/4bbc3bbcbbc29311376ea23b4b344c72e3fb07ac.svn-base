#include "TreeNode.h"

// Your function here

TreeNode *makeFullLeft(int n) {
  int a = 0;
  TreeNode* right = new TreeNode();
  right->data_ = a + 3;

  TreeNode* re = new TreeNode(a, leftN(a+2, n), right);
  return re;
}

TreeNode* leftN(int b, int n) {
  TreeNode* subRoot = new TreeNode();

  if (b+3 == n) {
    TreeNode* subRoot = new TreeNode();
    subRoot->data_ = b;

    TreeNode* right = new TreeNode();
    right->data_ = b + 3;

    TreeNode* left = new TreeNode();
    right->data_ = b + 2;

    subRoot->right_ = right;
    subRoot->left_ = left;

    return subRoot;
  }

  while (b+3 <= n) {
    TreeNode* subRoot = new TreeNode();
    subRoot->data_ = b;

    TreeNode* right = new TreeNode();
    right->data_ = b + 3;

    subRoot->right_ = right;
    subRoot->left_ = leftN(b+2, n);
  }
  return subRoot;

}

// Methods and functions we provide following.
// You should not need to edit this code.

TreeNode::TreeNode(int data, TreeNode *left, TreeNode *right) :
    data_(data), left_(left), right_(right) {}

TreeNode::~TreeNode() {
    if (left_ != NULL)
        delete left_;
    if (right_ != NULL)
        delete right_;
}

bool equal(TreeNode *n1, TreeNode *n2) {
    if (n1 == NULL)
        return n2 == NULL;

    if (n2==NULL)
        return false;

    return (n1->getData() == n2->getData() &&
            equal(n1->getLeft(),n2->getLeft()) &&
            equal(n1->getRight(),n2->getRight()));
}

int TreeNode::getData() const {
    return data_;
}

TreeNode *TreeNode::getLeft() const {
    return left_;
}

TreeNode *TreeNode::getRight() const {
    return right_;
}
