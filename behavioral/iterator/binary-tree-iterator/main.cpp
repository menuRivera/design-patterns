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
    // this code was wrong, provocated a crash
    // this->left->tree = this->right->tree = tree;
    // this->left->parent = this->right->parent = parent;
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
  BinaryTree(Node<T> *root) : root(root), pre_order(*this) {
    root->set_tree(this);
  }
  BinaryTree() : root(nullptr) {}

  ~BinaryTree() {
    if (root)
      delete root;
  }

  template <typename U> struct PreOrderIterator {
    Node<U> *current;

    PreOrderIterator(Node<U> *current) : current(current) {}

    bool operator!=(const PreOrderIterator<U> &other) const {
      return current != other.current;
    }

    // wtf is this
    PreOrderIterator<U> &operator++() {
      if (current->right) {
        current = current->right;
        while (current->left)
          current = current->left;
      } else {
        Node<T> *p = current->parent;
        while (p && current == p->right) {
          current = p;
          p = p->parent;
        }
        current = p;
      }
      return *this;
    }

    Node<U> &operator*() { return *current; }
  };

  typedef PreOrderIterator<T> iterator;

  struct PreOrderTraversal {
    BinaryTree &tree;
    PreOrderTraversal(BinaryTree &tree) : tree(tree) {}

    iterator begin() { return tree.begin(); }
    iterator end() { return tree.end(); }
  } pre_order;

  iterator begin() {
    if (!root)
      return iterator{nullptr};
    Node<T> *n = root;
    if (n)
      while (n->left)
        n = n->left;

    // get left most element
    return iterator{n};
  }

  iterator end() { return iterator{nullptr}; }
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

  cout << "root: " << family.root->value << endl;
  cout << "left: " << family.root->left->value << endl;
  cout << "left.left: " << family.root->left->left->value << endl;
  cout << "left.right: " << family.root->left->right->value << endl;
  cout << "right: " << family.root->right->value << endl;

  cout << endl;

  cout << "family.begin(): " << family.begin().current->value << endl;
  // cout << "family.end(): " << family.end().current->value << endl; // error

  cout << endl;

  // traversal
  for (auto it = family.begin(); it != family.end(); ++it) {
    cout << (*it).value << "\n";
  }

  // using pre_order
  for (const auto &it : family.pre_order) {
    cout << it.value << "\n";
  }
}
