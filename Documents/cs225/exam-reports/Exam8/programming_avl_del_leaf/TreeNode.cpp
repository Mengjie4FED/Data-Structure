#include "TreeNode.h"
#include <iostream>
#include <cmath>

// Part 1 code

void rotateRight(TreeNode *& root) {

    TreeNode *nuRoot = root->left_;
    root->left_ = nuRoot->right_;
    nuRoot->right_ = root;

    root = nuRoot;

    updateHeight(root);
    updateHeight(root->right_);
    return;
}


void rotateLeft(TreeNode *& root) {

    TreeNode *nuRoot = root->right_;
    root->right_ = nuRoot->left_;
    nuRoot->left_ = root;

    root = nuRoot;

    updateHeight(root);
    updateHeight(root->left_);
    return;
}

void rotateLeftRight(TreeNode* &root) {
    rotateLeft(root->left_);
    rotateRight(root);
}


void rotateRightLeft(TreeNode* &root) {
    rotateRight(root->right_);
    rotateLeft(root);
}

// Your Code

void remove(TreeNode* &root, int val) {
    // Your code here
    if (root == NULL) {
      return;
    }

    if (val < root->val_) {
      remove(root->left_, val);
      rebalance(root);
    } else if (val > root->val_) {
      remove(root->right_, val);
      rebalance(root);
    } else {
      if (root->left_ == NULL && root->right_ == NULL) {
        delete root;
        root = NULL;
      } else if (root->left_ != NULL) {
        root->val_ = root->left_->val_;
        delete root->left_;
        root->left_ = NULL;
      } else if (root->right_ != NULL) {
        root->val_ = root->right_->val_;
        delete root->right_;
        root->right_ =NULL;
      }
      rebalance(root);
    }
}

void rebalance(TreeNode* &root) {
    if (root == NULL) {return;}

    int heightRoot = heightOrNeg1(root->right_) - heightOrNeg1(root->left_);
    if (heightRoot == -2) {
      int heightLeft = heightOrNeg1(root->left_->right_) - heightOrNeg1(root->left_->left_);
      if (heightLeft == -1) {
        rotateRight(root);
        updateHeight(root->right_);
        updateHeight(root);
      } else {
        rotateLeftRight(root);
        updateHeight(root->left_);
        updateHeight(root->right_);
        updateHeight(root);
      }
    }
    if (heightRoot == 2) {
      int heightRight = heightOrNeg1(root->right_->right_) - heightOrNeg1(root->right_->left_);
      if (heightRight == 1) {
        rotateLeft(root);
        updateHeight(root->left_);
        updateHeight(root);
      } else {
        rotateRightLeft(root);
        updateHeight(root->right_);
        updateHeight(root->left_);
        updateHeight(root);
      }
    }
    updateHeight(root);
}

// Helper functions

int heightOrNeg1(TreeNode *root) {
    if (root==NULL)
        return -1;
    else
        return root->height_;
}

void updateHeight(TreeNode * node) {
    node->height_ = 1 + std::max(heightOrNeg1(node->right_), heightOrNeg1(node->left_));
}

using namespace std;

void show(TreeNode *t1) {
    if (t1==NULL) {
        cout << "x";
        return;
    }

    if (t1->left_ == NULL && t1->right_==NULL) {
        cout << t1->val_;
        return;
    }

    cout << "(" << t1-> val_ << " ";
    show(t1->left_);
    cout << " ";
    show(t1->right_);
    cout << ")";
}

void deleteTree(TreeNode* root)
{
    if (root == NULL) return;
    deleteTree(root->left_);
    deleteTree(root->right_);
    delete root;
    root = NULL;
}
