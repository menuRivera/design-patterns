/*
Given the following definition of a Node<T>, please implement preorder traversal
that returns a sequence of Ts. I have greatly simplified the problem by adding
an accumulator argument into the preorder_traversal()  function.
*/

#include <iostream>
#include <vector>

using namespace std;

template <typename T> struct Node {
  T value;
  // no need for a parent here i think
  Node *left{nullptr}, *right{nullptr}, *parent{nullptr};

  Node(T value) : value(value) {}

  Node(T value, Node<T> *left, Node<T> *right)
      : value(value), left(left), right(right) {
    left->parent = right->parent = this;
  }

  // traverse the node and its children preorder
  // and put all the results into `result`
  void preorder_traversal(vector<Node<T> *> &result) {
    result.push_back(this);
    if (left) {
      left->preorder_traversal(result);
    }
    if (right) {
      right->preorder_traversal(result);
    }
  }
};

int main() {
  Node root{"root",
            new Node("c1", new Node("c3", new Node("c5"), new Node("c6")),
                     new Node("c4")),
            new Node("c2")};
  // Node c1{"children1"};
  // Node c2{"children2"};
  // Node c3{"children3"};
  // Node c4{"children4"};
  // Node c5{"children5"};

  //     root
  //   /      \
  //   c1     c2
  //  /  \
  // c3  c4
  // / \
  // c5 c6

  // preorder traversal should look like this:
  // root, c1, c3, c5, c6, c4, c2

  vector<Node<const char *> *> result{};
  root.preorder_traversal(result);

  for (auto &n : result) {
    cout << n->value << endl;
  }

  return 0;
}
