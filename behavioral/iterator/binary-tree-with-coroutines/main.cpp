#include <coroutine>
#include <generator>
#include <iostream>
#include <string>

using namespace std;

template <typename T> struct BinaryTree;

template <typename T> struct Node {
  T value = T();
  Node<T> *left{nullptr}, *right{nullptr}, *parent{nullptr};
  BinaryTree<T> *tree{nullptr};

  Node(T value) : value(value) {}
  Node(T value, Node<T> *left, Node<T> *right)
      : value(value), left(left), right(right) {
    if (left) {
      left->tree = tree;
      left->parent = this;
    }
    if (right) {
      right->tree = tree;
      right->parent = this;
    }
  }

  void set_tree(BinaryTree<T> *t) {
    tree = t;
    if (left)
      left->set_tree(t);
    if (right)
      right->set_tree(t);
  }

  ~Node() {
    delete left;
    delete right;
  }
};

template <typename T> struct BinaryTree {
  Node<T> *root{nullptr};
  BinaryTree(Node<T> *root) : root(root) { root->set_tree(this); }
  BinaryTree() : root(nullptr) {}

  ~BinaryTree() {
    if (root)
      delete root;
  }

  // c++23 feature
  generator<Node<T> *> post_order() { return post_order_impl(root); }

private:
  generator<Node<T> *> post_order_impl(Node<T> *node) {
    if (node) {
      for (auto x : post_order_impl(node->left)) {
        co_yield x;
      }
      for (auto y : post_order_impl(node->right)) {
        co_yield y;
      }
      co_yield node;
    }
  }
};

int main() {
  //       me
  //     /    \
  // mother   father
  //   /  \
  // m'm  m'f
  BinaryTree<string> family{new Node<string>{
      "Me",
      new Node<string>{"Mother", new Node<string>{"Mother's mother"},
                       new Node<string>{"Mother's father"}},
      new Node<string>{"Fahter"}}};

  for (auto it : family.post_order()) {
    cout << it->value << endl;
  }
}
