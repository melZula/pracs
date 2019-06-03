#include <iostream>
#include <vector>

using namespace std;

template <class T, class Compare = std::less<T>>
class Tree {
private:
  class Node {
  public:
    T key;
    Node *parent;
    Node *left;
    Node *right;
    int height;
    Node(T key, Node *parent, Node *left, Node *right, int height = 0) :
    key(key), parent(parent), left(left), right(right), height(height) {
    }
  };

  Node* root;
  size_t size;
  Compare compare;

  // AVL methods
  int get_height(Node* node) {
    return node == nullptr ? 0 : node->height;
  }
  int get_balance(Node* node) {
    return node == nullptr ? 0 : get_height(node->left) - get_height(node->right);
  }
  Node* left_rotation(Node* node) {
    Node* parent = node->parent;
    Node* X = node->right;
    Node* B = X->left;

    X->left = node;
    node->right = B;
    X->parent = parent;
    node->parent = X;
    if (B != nullptr) {
      B->parent = node;
    }

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    X->height = 1 + max(get_height(X->left), get_height(X->right));

    return X;
  }
  Node* right_rotation(Node* node) {
    Node* parent = node->parent;
    Node* X = node->left;
    Node* B = X->right;

    X->right = node;
    node->left = B;
    X->parent = parent;
    node->parent = X;
    if (B != nullptr) {
      B->parent = node;
    }

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    X->height = 1 + max(get_height(X->left), get_height(X->right));

    return X;
  }
  void balance(Node*& node) {
    int balance = get_balance(node);
    if (balance > 1 && get_balance(node->left) >= 0) {
      node = right_rotation(node);
    } else if (balance < -1 && get_balance(node->right) <= 0) {
      node = left_rotation(node);
    } else if (balance > 1 && get_balance(node->left) < 0) {
      node->left = left_rotation(node->left);
      node = right_rotation(node);
    } else if (balance < -1 && get_balance(node->right) > 0) {
      node->right = right_rotation(node->right);
      node = left_rotation(node);
    }
  }
  void make_balanced(Node* node) {
    if (node != nullptr) {
      node->height = 1 + max(get_height(node->left), get_height(node->right));
      balance(node);
      make_balanced(node->parent);
    }
  }

  // functional methods
  void insert(Node*& node, Node* parent, const T& key) {
    if (node == nullptr) {
      node = new Node(key, parent, nullptr, nullptr, 1);
    } else if (compare(key, node->key)) {
      insert(node->left, node, key);
    } else if (compare(node->key, key)) {
      insert(node->right, node, key);
    }
    node->height = 1 + max(get_height(node->left), get_height(node->right));
    balance(node);
  }
  bool search(Node* node, const T& key) {
    if (node == nullptr) {
      return false;
    } else if (key == node->key) {
      return true;
    } else {
      return search(compare(key, node->key) ? node->left : node->right, key);
    }
  }
  static Node* get_minimum_node(Node* node) {
    if (node == nullptr) {
      return nullptr;
    }
    Node* currentNode = node;
    while (currentNode->left != nullptr) {
      currentNode = currentNode->left;
    }
    return currentNode;
  }
  static Node* get_maximum_node(Node* node) {
    if (node == nullptr) {
      return nullptr;
    }
    Node* currentNode = node;
    while (currentNode->right != nullptr) {
      currentNode = currentNode->right;
    }
    return currentNode;
  }
  void erase_node(Node*& node) {
    if (node == nullptr) {
      return;
    }
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      node = nullptr;
    } else if (node->left == nullptr) {
      Node* parent = node->parent;
      Node* right = node->right;
      delete node;
      node = right;
      node->parent = parent;
      make_balanced(node);
    } else if (node->right == nullptr) {
      Node* parent = node->parent;
      Node* left = node->left;
      delete node;
      node = left;
      node->parent = parent;
      make_balanced(node);
    } else {
      Node* minimum = get_minimum_node(node->right);
      Node* minimum_parent = minimum->parent;
      if (minimum->right != nullptr) {
        minimum->right->parent = minimum->parent;
      }
      if (minimum == minimum->parent->left) {
        minimum->parent->left = minimum->right;
      } else if (minimum == minimum->parent->right) {
        minimum->parent->right = minimum->right;
      }
      node->key = minimum->key;
      delete minimum;
      make_balanced(minimum_parent);
    }
  }
  void erase(T key, Node*& node) {
    if (node == nullptr) {
      return;
    }
    if (key == node->key) {
      erase_node(node);
    } else {
      erase(key, compare(key, node->key) ? node->left : node->right);
    }
    if (node != nullptr) {
      node->height = 1 + max(get_height(node->left), get_height(node->right));
      balance(node);
    }
  }
  static Node* get_previous_node(Node* node) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->left != nullptr) {
      return get_maximum_node(node->left);
    }
    Node* parent = node->parent;
    while (parent != nullptr && node == parent->left) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }
  static Node* get_next_node(Node* node) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->right != nullptr) {
      return get_minimum_node(node->right);
    }
    Node* parent = node->parent;
    while (parent != nullptr && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }
  Node* get_node(const T& key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (key == node->key) {
      return node;
    }
    return get_node(key, compare(key, node->key) ? node->left : node->right);
  }

  // traversals
  void inorder_traversal(Node* node) {
    if (node != nullptr) {
      inorder_traversal(node->left);
      cout << node->key << " ";
      inorder_traversal(node->right);
    }
  }
  void insert_keys(const Tree& tree, Node* node) {
    if (node != nullptr) {
      insert_keys(tree, node->left);
      insert(node->key);
      insert_keys(tree, node->right);
    }
  }
  void erase_all(Node* node) {
    if (node != nullptr) {
      erase_all(node->left);
      erase_all(node->right);
      delete node;
    }
  }

  // сlass Iterator
  template <bool is_const>
  class Iterator {
    Node* node;
    const Tree* tree;
  public:
    Iterator(const Tree* tree, Node* node) : tree(tree), node(node) {}
    T& operator * () {
      return node->key;
    }
    bool operator == (const Iterator& iterator) const {
      return tree == iterator.tree && node == iterator.node;}
      bool operator != (const Iterator& iterator) const {
        return !(tree == iterator.tree && node == iterator.node);
      }
      Iterator& operator ++ () {
        if (node == nullptr) {
          node = get_minimum_node(tree->root);
        } else {
          node = get_next_node(node);
        }
        return *this;
      }
      Iterator operator ++ (int) {
        Iterator iterator(tree, node);
        if (node == nullptr) {
          node = get_minimum_node(tree->root);
        } else {
          node = get_next_node(node);
        }
        return iterator;
      }
      Iterator& operator -- () {
        if (node == nullptr) {
          node = get_maximum_node(tree->root);
        } else {
          node = get_previous_node(node);
        }
        return *this;
      }
      Iterator operator -- (int) {
        Iterator iterator(tree, node);
        if (node == nullptr) {
          node = get_maximum_node(tree->root);
        } else {
          node = get_previous_node(node);
        }
        return iterator;
      }
      Iterator operator + (int step) {
        Iterator iterator(tree, node);
        for (int i = 0; i < step; i++) {
          ++iterator;
        }
        return iterator;
      }
      Iterator operator - (int step) {
        Iterator iterator(tree, node);
        for (int i = 0; i < step; i++) {
          --iterator;
        }
        return iterator;
      }
    };

  public:
    // Tree
    Tree() {
      root = nullptr;
      size = 0;
    } // default constructor
    Tree(const Tree& tree) {
      insert_keys(tree, tree.root);
    } // copy constructor
    Tree& operator = (const Tree& tree) {
      insert_keys(tree, tree.root);
      return *this;
    }
    ~Tree() {
      erase_all();
    } // destructor

    typedef Iterator<true> const_iterator;
    typedef Iterator<false> iterator;

    // user methods
    bool search(const T& key) {
      return search(root, key);
    }
    iterator insert(const T& key) {
      if (!search(key)) {
        insert(root, nullptr, key);
        size++;
      }
      return iterator(this, get_node(key, root));
    }
    iterator find(const T& key) {
      return iterator(this, get_node(key, root));
    }
    const_iterator find(const T& key) const {
      return const_iterator(this, get_node(key, root));
    }
    iterator remove(const T& key) {
      return iterator(this, erase(key) ? nullptr : get_node(key, root));
    }
    bool erase(const T& key) {
      if (search(key)) {
        erase(key, root);
        size--;
        return true;
      } else {
        return false;
      }
    }
    void erase_all() {
      erase_all(root);
      root = nullptr;
      size = 0;
    }
    void print() {
      inorder_traversal(root);
    }
    bool empty() const {
      return size == 0;
    }
    size_t get_size() const {
      return size;
    }

    // iterators
    iterator begin() {
      return iterator(this, get_minimum_node(root));
    }
    const_iterator cbegin() {
      return const_iterator(this, get_minimum_node(root));
    }
    iterator end() {
      return iterator(this, nullptr);
    }
    const_iterator cend() {
      return const_iterator(this, nullptr);
    }
  };

  template <class T, class Compare = std::less<T>>
  ostream& operator << (ostream& stream, Tree<T>& tree) {
    tree.print();
    return stream;
  }

  template <class T>
  class Compare {
  public:
    bool operator () (const T& a, const T& b) const {
      return a > b;
    }
  };





  int main() {
    Compare<int> compare;
    Tree<int, std::less<int>> tree;
    vector<int> v = {5,3,6,8,3,1};
    for (int element : v) {
      tree.insert(element);
    }
    tree.insert(10);
    tree.print();

    return 0;
  }
