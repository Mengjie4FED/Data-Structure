/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 #include <algorithm>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tempR = t->right;
    t->right = tempR->left;
    tempR->left = t;

    tempR->height = 1 + max(height(tempR->left), height(tempR->right));
    t->height = 1 + max(height(t->left), height(t->right));
    t = tempR;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tempL = t->left;
    t->left = tempL->right;
    tempL->right = t;

    tempL->height = 1 + max(height(tempL->left), height(tempL->right));
    t->height = 1 + max(height(t->left), height(t->right));
    t = tempL;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
      return;
    }

    int balance = height(subtree->right) - height(subtree->left);

    if (balance == -2) {
      int leftBal = height(subtree->left->right) - height(subtree->left->left);
      if (leftBal == -1) {
        rotateRight(subtree);


      } else {
        rotateLeftRight(subtree);
      }
    }

    if (balance == 2) {
      int rightBal = height(subtree->right->right) - height(subtree->right->left);
      if (rightBal == 1) {
        rotateLeft(subtree);
      } else {
        rotateRightLeft(subtree);
      }
    }

}

template <class K, class V>
int AVLTree<K, V>::height(Node* subRoot) {
  if (subRoot == NULL){
    return -1;
  } else {
    return subRoot->height;
  }
}


template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
      subtree = new Node(key, value);
    } else if (key < subtree->key) {
      insert(subtree->left, key, value);
      rebalance(subtree);
    } else if (key > subtree->key) {
      insert(subtree->right, key, value);
      rebalance(subtree);
    }

    subtree->height = 1 + max(height(subtree->left), height(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            /*Node* preN = swap(subtree);
            Node* delN = preN->right;
            Node* subL = delN->left;

            preN->right = subL;
            delete delN;
            delN = NULL;*/

            Node* curr = subtree->left;
            if (curr->right == NULL) {
              swap(subtree, curr);
              delete curr;
              //curr = NULL;
              subtree->left = NULL;

            } else {
              while (curr->right->right != NULL) {
                curr = curr->right;
              }
              swap(subtree, curr->right);
              Node* tempLeft = curr->right->left;
              delete curr->right;
              curr->right = tempLeft;

            }


        } else {
            /* one-child remove */
            // your code here
            if (subtree->left == NULL) {
              subtree->key = subtree->right->key;
              subtree->value = subtree->right->value;
              delete subtree->right;
              subtree->right = NULL;
            } else if (subtree->right == NULL) {
              subtree->key = subtree->left->key;
              subtree->value = subtree->left->value;
              delete subtree->left;
              subtree->left = NULL;
            }
        }
        // your code here
        rebalance(subtree);
    }
}


/*template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::swapReturnPre(Node*& subtree) {
  Node* curr = subtree->left;
  while (curr->right->right != NULL) {
    curr = curr->right;
  }

  Node* preN = curr
  curr = curr->right;

  Node* temp = subtree;
  subtree->key = curr->key;
  subtree->value = curr->value;
  curr->key = temp->key;
  curr->value = temp->value;

  return preN;
}*/
