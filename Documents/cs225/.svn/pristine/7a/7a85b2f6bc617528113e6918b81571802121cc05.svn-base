/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  while ( head_ != NULL ) {
    ListNode* nextN = head_->next;

    delete head_; head_= NULL;
    head_ = nextN;
  }

  //head_= NULL;
  tail_= NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);

  if (this->empty()) {
    head_ = newNode;
    tail_ = newNode;
    newNode->prev = NULL;
    newNode->next = NULL;
    length_ += 1;
    return;
  }

  ListNode* node2 = this->head_;
  this->head_ = newNode;
  newNode->prev = NULL;
  newNode->next = node2;
  newNode->next->prev = newNode;
  length_ += 1;

  return;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);

  if ((*this).empty()) {
    this->head_ = newNode;
    this->tail_ = newNode;
    newNode->prev = NULL;
    newNode->next = NULL;
    length_ += 1;
    return;
  }
  ListNode* nodel2 = this->tail_;
  this->tail_ = newNode;
  newNode->prev = nodel2;
  newNode->next = NULL;
  newNode->prev->next = newNode;
  length_ += 1;
  return;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1
    ListNode* spPrev = startPoint->prev;
    ListNode* endNext = endPoint->next;

    ListNode* curr = startPoint;

    while (curr != endNext) {
      ListNode* currNext = curr->next;
      curr->next = curr->prev;
      curr->prev = currNext;
      curr = currNext;
   }

   startPoint->next = endNext;
   endPoint->prev = spPrev;

  if (spPrev != NULL) {
    spPrev->next = endPoint;
  }
  if (endNext != NULL) {
    endNext->prev = startPoint;
  }

  curr = endPoint;
  endPoint = startPoint;
  startPoint = curr;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  ListNode* currH = head_;
  ListNode* currT = head_;
  int a = 1;

  while (currH != NULL) {
    currT = currH;
    for (int i = 1; i < n; i++) {
        if (currT->next != NULL) {
        currT = currT->next;
      }
    }

    if (a == 1) {head_ = currT;}
    a += 1;

    reverse(currH, currT);
    currH = currT->next;
  }

  tail_ = currT;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  while (curr->next != tail_) {
    ListNode* currN = curr->next;
    curr->next = currN->next;
    currN->next->prev = curr;

    currN->prev = tail_;
    tail_->next = currN;
    currN->next = NULL;
    tail_ = currN;

    curr = curr->next;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    if (start == NULL) {
      return NULL;
    }

    if (splitPoint == 0) {
      return start;
    }

    ListNode* newStartN = start;
    for (int i = 0; i < splitPoint; i++) {
      newStartN = newStartN->next;
    }
    if (newStartN != NULL) {
      newStartN->prev->next = NULL;
      newStartN->prev = NULL;
    }
    return newStartN;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* currFirst = first;
  ListNode* currSecond = second;
  ListNode* tempSecond = second;
  ListNode* tailF = first;

  if ( currSecond->data < currFirst->data ) {
    tempSecond = currSecond->next;
    currSecond->next = currFirst;
    currFirst->prev = currSecond;
    first = currSecond;
    currSecond = tempSecond;
    currFirst = first->next;
    tailF = currFirst;
  }

  while (currFirst != NULL && currSecond != NULL) {


      if (currSecond->data < currFirst->data) {
        tempSecond = currSecond->next;
        currSecond->prev = currFirst->prev;
        currSecond->next = currFirst;
        currFirst->prev = currSecond;
        currSecond->prev->next = currSecond;

        currSecond = tempSecond;
        tailF = currFirst;

      } else {
        tailF = currFirst;
        currFirst = currFirst->next;
      }
  }

  if (currSecond == NULL) {
    return first;
  } else {

    tailF->next = currSecond;
    currSecond->prev = tailF;

    return first;
  }

}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    if (chainLength == 1) {return start;}
    int splitPoint = chainLength/2;
    ListNode* right = split(start, splitPoint);
    ListNode* left = start;

    left = mergesort(left, splitPoint);
    right = mergesort(right, chainLength-splitPoint);
    return merge(left, right);
}
