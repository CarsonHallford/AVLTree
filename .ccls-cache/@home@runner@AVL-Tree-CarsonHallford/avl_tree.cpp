// insert_recursive written by Aiden Wolter
// rotate_right & rotate_left written by Carson Hallford
#include "avl_tree.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>

// Recalculate the height of |t| by taking the maximum height
// of the children, then assign it back to |t->height|.
void recalculate_height(Node* t) {
  // TODO: implement!
  assert(t != nullptr);
  int height = 0;
  bool left_valid = (t->left != nullptr);
  bool right_valid = (t->right != nullptr);
  int left_value = 0;
  if (left_valid) {
    left_value = t->left->height;
  }
  int right_value = 0;
  if (right_valid) {
    right_value = t->right->height;
  }
  t->height = 1 + std::max(left_value, right_value);
}

// Calculate the balance factor of |t| by diffing the height
// of the left and right children.
int calculate_bf(Node* t) {
  int bf = 0;
  if (t->left != nullptr) {
    bf += t->left->height;
  }
  if (t->right != nullptr) {
    bf -= t->right->height;
  }
  return bf;
  // TODO: implement!
}

// Rotate |n| left and adjust the heights.
Node* rotate_left(Node* n) {
  assert(n->right != nullptr);
  // TODO: implement!
  Node* b = n->right;
  n->right = n->right->left;
  b->left = n;
  recalculate_height(n);
  return b;
}

// Rotate |n| right and adjust the heights.
Node* rotate_right(Node* n) {
  assert(n->left != nullptr);
  // TODO: implement!
  Node* b = n->left;
  b->left = n->left->right;
  b->right = n;
  recalculate_height(b);
  return n;
}

// Insert |n| into the tree at |t|, and return the head of the
// new tree.
Node* insert_recursive(Node* t, int data) {
  // TODO: implement!
  // Insert recursively.
  if (t == nullptr) return new Node(data);
  if (data < t->data) {
    t->left = insert_recursive(t->left, data);
  } else {
    t->right = insert_recursive(t->right, data);
  }

  // TODO: implement!
  // While recursing back up the stack, readjust the heights, and
  // make sure that the balance factor is between -1 and 1.
  // Rotate if necessary to rebalance.
  recalculate_height(t);
  int bf = calculate_bf(t);

  if (bf > 1) {
    // right rotation
    if (data < t->left->data) {
      t = rotate_right(t);

    }
    // left-right rotation
    else {
      t->left = rotate_left(t->left);
      t = rotate_right(t);
    }

  } else if (bf < -1) {
    // left rotation
    if (data >= t->right->data) {
      t = rotate_left(t);
    }
    // right-left rotation
    else {
      t->right = rotate_right(t->right);
      t = rotate_left(t);
    }
  }

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
