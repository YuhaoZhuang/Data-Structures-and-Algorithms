#ifndef TREEMAP_H_
#define TREEMAP_H_

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <utility>
#include <exception>
#include <cstdlib>

template <typename K, typename V>
class Treemap {
 public:
  //
  // @@@ The class's public API below should _not_ be modified @@@
  //

  // * Capacity
  // Returns number of key-value mappings in map --O(1)
  size_t Size();
  // Returns true if map is empty --O(1)
  bool Empty();

  // * Modifiers
  // Insert @key in map --O(log N) on average
  void Insert(const K &key, const V &value);
  // Remove @key from map --O(log N) on average
  void Remove(const K &key);

  // * Lookup
  // Return value corresponding to @key --O(log N) on average
  const V& Get(const K &key);

  // Return greatest key less than or equal to @key --O(log N) on average
  const K& FloorKey(const K &key);
  // Return least key greater than or equal to @key --O(log N) on average
  const K& CeilKey(const K &key);

  // Return whether @key is found in map --O(log N) on average
  bool ContainsKey(const K& key);
  // Return whether @value is found in map --O(N)
  bool ContainsValue(const V& value);

  // Return max key in map --O(log N) on average
  const K& MaxKey();
  // Return min key in map --O(log N) on average
  const K& MinKey();

 private:
    struct Node {
      K key;
      V value;
      std::unique_ptr<Node> left;
      std::unique_ptr<Node> right;
    };
    size_t size = 0;
    std::unique_ptr<Node> root;
    void CheckRoot(std::unique_ptr<Node> &n);
    void Insert(std::unique_ptr<Node> &n, const K &key, const V &value);
    void Remove(std::unique_ptr<Node> &n, const K &key);
    Node* Min(Node *n);
    Node* Max(Node *n);
    bool ContainsValue(Node *n, const V& value);
    Node* FloorKey(std::unique_ptr<Node> &n, const K &key);
    Node* CeilKey(std::unique_ptr<Node> &n, const K &key);
};

template <typename K, typename V>
size_t Treemap<K, V>::Size() {
  return size;
}

template <typename K, typename V>
bool Treemap<K, V>::Empty() {
  if (size == 0) {
    return true;
  } else {
    return false;
  }
}

// Check if the root is a nullptr, or if treemap empty
template <typename K, typename V>
void Treemap<K, V>::CheckRoot(std::unique_ptr<Node> &n) {
  if (!n) {
    throw std::out_of_range("Root Node does not exist");
  }
}

template <typename K, typename V>
void Treemap<K, V>::Insert(const K &key, const V &value) {
  Insert(root, key, value);
}

// Helper function for Insert
template <typename K, typename V>
void Treemap<K, V>::Insert(std::unique_ptr<Node> &n, const K &key,
  const V &value) {
  if (!n) {
    n = std::unique_ptr<Node>(new Node{key, value});
    size++;
  } else if (key < n->key) {
    Insert(n->left, key, value);
  } else if (key > n->key) {
    Insert(n->right, key, value);
  } else {
    throw std::invalid_argument("Node already exist");
  }
}

// Helper function for returning the smallest node
template <typename K, typename V>
typename Treemap<K, V>::Node* Treemap<K, V>::Min(Node *n) {
  while (n->left) {
    n = n->left.get();
  }
  return n;
}

// Helper function for returning the largest node
template <typename K, typename V>
typename Treemap<K, V>::Node* Treemap<K, V>::Max(Node *n) {
  while (n->right) {
    n = n->right.get();
  }
  return n;
}

template <typename K, typename V>
void Treemap<K, V>::Remove(const K &key) {
  auto a = size;
  Remove(root, key);
  if (size == a) {
    throw std::invalid_argument("key not found");
  }
}

// Helper function for remove
template <typename K, typename V>
void Treemap<K, V>::Remove(std::unique_ptr<Node> &n, const K &key) {
  if (!n) {
    return;
  }
  if (key < n->key) {
    Remove(n->left, key);
  } else if (key > n->key) {
    Remove(n->right, key);
  } else if (key == n->key) {
    if (n->left && n->right) {
      auto n_min = Min(n->right.get());
      n->key = n_min->key;
      n->value = n_min->value;
      Remove(n->right, n->key);
    } else {
      n = std::move((n->left) ? n->left : n->right);
      size--;
    }
  }
}

template <typename K, typename V>
const V& Treemap<K, V>::Get(const K &key) {
  CheckRoot(root);
  Node *n = root.get();
  while (n) {
    if (key == n->key) {
      return n->value;
    } else {
      if (key < n->key) {
        n = n->left.get();
      } else if (key > n->key) {
        n = n->right.get();
      }
    }
  }
  throw std::invalid_argument("Node doesn't exist");
}

// Helper function for floorkey, return the node that
// has greatest value smaller than key
template <typename K, typename V>
typename Treemap<K, V>::Node* Treemap<K, V>::FloorKey
(std::unique_ptr<Node> &n, const K &key) {
  if (!n) {
    return nullptr;
  } else if (n->key > key) {
    auto n_temp = FloorKey(n->left, key);
    if (!n_temp) {
      return nullptr;
    } else {
      return n_temp;
    }
  } else if (n->key < key) {
    auto n_temp = FloorKey(n->right, key);
    if (!n_temp) {
      return n.get();
    } else {
      return n_temp;
    }
  } else if (n->key == key) {
    return n.get();
  }
  return nullptr;
}

template <typename K, typename V>
const K& Treemap<K, V>::FloorKey(const K &key) {
  CheckRoot(root);
  CheckRoot(root);
  Node *n = FloorKey(root, key);
  if (!n) {
    throw std::invalid_argument("No larger key");
  } else {
    return n->key;
  }
}

// Helper function for CeilKey, return the node that
// has the smallest value larger than the key
template <typename K, typename V>
typename Treemap<K, V>::Node* Treemap<K, V>::CeilKey
(std::unique_ptr<Node> &n, const K &key) {
  if (!n) {
    return nullptr;
  } else if (n->key > key) {
    auto n_temp = CeilKey(n->left, key);
    if (!n_temp) {
      return n.get();
    } else {
      return n_temp;
    }
  } else if (n->key < key) {
    auto n_temp = CeilKey(n->right, key);
    if (!n_temp) {
      return nullptr;
    } else {
      return n_temp;
    }
  } else if (n->key == key) {
    return n.get();
  }
  return nullptr;
}

template <typename K, typename V>
const K& Treemap<K, V>::CeilKey(const K &key) {
  CheckRoot(root);
  Node *n = CeilKey(root, key);
  if (!n) {
    throw std::invalid_argument("No larger key");
  } else {
    return n->key;
  }
}

template <typename K, typename V>
bool Treemap<K, V>::ContainsKey(const K& key) {
  Node *n = root.get();
  while (n) {
    if (key == n->key) {
      return true;
    } else if (key < n->key) {
      n = n->left.get();
    } else if (key > n->key) {
      n = n->right.get();
    }
  }
  return false;
}

// Helper function for ContainsValue, return true if value
// matches, false if not
template <typename K, typename V>
bool Treemap<K, V>::ContainsValue(Node *n, const V& value) {
  if (!n) {
    return false;
  }
  if (n->value == value) {
    return true;
  } else if (ContainsValue(n->left.get(), value) ||
    ContainsValue(n->right.get(), value)) {
    return true;
  }
  return false;
}

template <typename K, typename V>
bool Treemap<K, V>::ContainsValue(const V& value) {
  return ContainsValue(root.get(), value);
}

template <typename K, typename V>
const K& Treemap<K, V>::MaxKey() {
  CheckRoot(root);
  Node *n = Max(root.get());
  return n->key;
}

template <typename K, typename V>
const K& Treemap<K, V>::MinKey() {
  CheckRoot(root);
  Node *n = Min(root.get());
  return n->key;
}

#endif  // TREEMAP_H_
