#include "avl_tree.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>

// Recalculate the height of |t| by taking the maximum height
// of the children, then assign it back to |t->height|.
void recalculate_height(Node* t) {
  // TODO: implement!
}

// Calculate the balance factor of |t| by diffing the height
// of the left and right children.
int calculate_bf(Node* t) {
  // TODO: implement!
  return 0;
}

// Rotate |n| left and adjust the heights.
Node* rotate_left(Node* n) {
  assert(n->right != nullptr);
  // TODO: implement!
  return n;
}

// Rotate |n| right and adjust the heights.
Node* rotate_right(Node* n) {
  assert(n->left != nullptr);
  // TODO: implement!
  return n;
}

// Insert |n| into the tree at |t|, and return the head of the
// new tree.
Node* insert_recursive(Node* t, int data) {
  // TODO: implement!
  // Insert recursively.

  // TODO: implement!
  // While recursing back up the stack, readjust the heights, and
  // make sure that the balance factor is between -1 and 1.
  // Rotate if necessary to rebalance.
  return t;
}

// Insert |data| into the tree, and rebalance if necessary.
void AVLTree::insert(int data) { head = insert_recursive(head, data); }

// Print the tree's contents.
void AVLTree::print() {
  if (head == nullptr) return;
  int indentation = 32;
  bool stop = false;

  // BFS
  std::queue<Node*> q;
  q.push(head);
  while (!stop) {
    stop = true;
    std::cout << std::string((indentation / 2) - 1, ' ');

    // Add the next layer of children, and remove the current layer.
    // Print as we go.
    int size = q.size();
    for (int i = 0; i < size; i++) {
      // Print the current node.
      Node* n = q.front();
      if (n == nullptr) {
        std::cout << "_";
      } else {
        std::cout << n->data;
      }
      if (i == size - 1) {
        std::cout << std::endl;
      } else {
        std::cout << std::string(indentation - 1, ' ');
      }

      // Add the children, and count the
      if (n != nullptr) {
        q.push(n->left);
        q.push(n->right);
        if (n->left != nullptr || n->right != nullptr) stop = false;
      } else {
        q.push(nullptr);
        q.push(nullptr);
      }

      // Remove the current.
      q.pop();
    }

    indentation /= 2;
  }
}
