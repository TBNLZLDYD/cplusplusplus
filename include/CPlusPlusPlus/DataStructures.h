//===- DataStructures.h ---------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ high-level data structures header file.
//
//===----------------------------------------------------------------------===//

#ifndef CPLUSPLUSPLUS_DATASTRUCTURES_H
#define CPLUSPLUSPLUS_DATASTRUCTURES_H

#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <limits>

namespace CPlusPlusPlus {
namespace DataStructures {

// AVL Tree
template <typename T, typename Compare = std::less<T>>
class avl_tree {
private:
  struct Node {
    T value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    int height;

    Node(const T& val) : value(val), left(nullptr), right(nullptr), height(1) {}
  };

  std::unique_ptr<Node> root;
  Compare comp;

  int height(const Node* node) const {
    return node ? node->height : 0;
  }

  int balance_factor(const Node* node) const {
    return node ? height(node->left.get()) - height(node->right.get()) : 0;
  }

  std::unique_ptr<Node> rotate_right(std::unique_ptr<Node> y) {
    std::unique_ptr<Node> x = std::move(y->left);
    std::unique_ptr<Node> T2 = std::move(x->right);

    x->right = std::move(y);
    x->right->left = std::move(T2);

    x->right->height = std::max(height(x->right->left.get()), height(x->right->right.get())) + 1;
    x->height = std::max(height(x->left.get()), height(x->right.get())) + 1;

    return x;
  }

  std::unique_ptr<Node> rotate_left(std::unique_ptr<Node> x) {
    std::unique_ptr<Node> y = std::move(x->right);
    std::unique_ptr<Node> T2 = std::move(y->left);

    y->left = std::move(x);
    y->left->right = std::move(T2);

    y->left->height = std::max(height(y->left->left.get()), height(y->left->right.get())) + 1;
    y->height = std::max(height(y->left.get()), height(y->right.get())) + 1;

    return y;
  }

  std::unique_ptr<Node> insert(std::unique_ptr<Node> node, const T& value) {
    if (!node) {
      return std::make_unique<Node>(value);
    }

    if (comp(value, node->value)) {
      node->left = insert(std::move(node->left), value);
    } else if (comp(node->value, value)) {
      node->right = insert(std::move(node->right), value);
    } else {
      return node; // Duplicate values not allowed
    }

    node->height = std::max(height(node->left.get()), height(node->right.get())) + 1;

    int bf = balance_factor(node.get());

    // Left Left case
    if (bf > 1 && comp(value, node->left->value)) {
      return rotate_right(std::move(node));
    }

    // Right Right case
    if (bf < -1 && comp(node->right->value, value)) {
      return rotate_left(std::move(node));
    }

    // Left Right case
    if (bf > 1 && comp(node->left->value, value)) {
      node->left = rotate_left(std::move(node->left));
      return rotate_right(std::move(node));
    }

    // Right Left case
    if (bf < -1 && comp(value, node->right->value)) {
      node->right = rotate_right(std::move(node->right));
      return rotate_left(std::move(node));
    }

    return node;
  }

  Node* find_min(Node* node) const {
    while (node && node->left) {
      node = node->left.get();
    }
    return node;
  }

  std::unique_ptr<Node> remove(std::unique_ptr<Node> node, const T& value) {
    if (!node) {
      return nullptr;
    }

    if (comp(value, node->value)) {
      node->left = remove(std::move(node->left), value);
    } else if (comp(node->value, value)) {
      node->right = remove(std::move(node->right), value);
    } else {
      if (!node->left) {
        return std::move(node->right);
      } else if (!node->right) {
        return std::move(node->left);
      }

      Node* min_node = find_min(node->right.get());
      node->value = min_node->value;
      node->right = remove(std::move(node->right), node->value);
    }

    node->height = std::max(height(node->left.get()), height(node->right.get())) + 1;

    int bf = balance_factor(node.get());

    // Left Left case
    if (bf > 1 && balance_factor(node->left.get()) >= 0) {
      return rotate_right(std::move(node));
    }

    // Left Right case
    if (bf > 1 && balance_factor(node->left.get()) < 0) {
      node->left = rotate_left(std::move(node->left));
      return rotate_right(std::move(node));
    }

    // Right Right case
    if (bf < -1 && balance_factor(node->right.get()) <= 0) {
      return rotate_left(std::move(node));
    }

    // Right Left case
    if (bf < -1 && balance_factor(node->right.get()) > 0) {
      node->right = rotate_right(std::move(node->right));
      return rotate_left(std::move(node));
    }

    return node;
  }

  bool contains(const Node* node, const T& value) const {
    if (!node) {
      return false;
    }

    if (comp(value, node->value)) {
      return contains(node->left.get(), value);
    } else if (comp(node->value, value)) {
      return contains(node->right.get(), value);
    } else {
      return true;
    }
  }

public:
  avl_tree() : root(nullptr), comp(Compare()) {}

  void insert(const T& value) {
    root = insert(std::move(root), value);
  }

  void remove(const T& value) {
    root = remove(std::move(root), value);
  }

  bool contains(const T& value) const {
    return contains(root.get(), value);
  }

  bool empty() const {
    return !root;
  }

  int height() const {
    return height(root.get());
  }
};

// Skip List
template <typename T, typename Compare>
class skip_list {
private:
  struct Node {
    T value;
    std::vector<std::unique_ptr<Node>> forward;

    Node(const T& val, int level) : value(val), forward(level, nullptr) {}
  };

  std::unique_ptr<Node> head;
  int max_level;
  int level;
  Compare comp;

  int random_level() {
    int lvl = 1;
    while (rand() % 2 && lvl < max_level) {
      lvl++;
    }
    return lvl;
  }

public:
  skip_list(int max_lvl = 16) : max_level(max_lvl), level(1), comp(Compare()) {
    head = std::make_unique<Node>(T(), max_level);
  }

  void insert(const T& value) {
    std::vector<Node*> update(max_level, nullptr);
    Node* current = head.get();

    for (int i = level - 1; i >= 0; i--) {
      while (current->forward[i] && comp(current->forward[i]->value, value)) {
        current = current->forward[i].get();
      }
      update[i] = current;
    }

    current = current->forward[0].get();

    if (!current || comp(current->value, value)) {
      int new_level = random_level();

      if (new_level > level) {
        for (int i = level; i < new_level; i++) {
          update[i] = head.get();
        }
        level = new_level;
      }

      auto new_node = std::make_unique<Node>(value, new_level);

      for (int i = 0; i < new_level; i++) {
        new_node->forward[i] = std::move(update[i]->forward[i]);
        update[i]->forward[i] = std::move(new_node);
        new_node = std::move(update[i]->forward[i]);
      }
    }
  }

  void remove(const T& value) {
    std::vector<Node*> update(max_level, nullptr);
    Node* current = head.get();

    for (int i = level - 1; i >= 0; i--) {
      while (current->forward[i] && comp(current->forward[i]->value, value)) {
        current = current->forward[i].get();
      }
      update[i] = current;
    }

    current = current->forward[0].get();

    if (current && !comp(current->value, value) && !comp(value, current->value)) {
      for (int i = 0; i < level; i++) {
        if (update[i]->forward[i].get() != current) {
          break;
        }
        update[i]->forward[i] = std::move(current->forward[i]);
      }

      while (level > 1 && !head->forward[level - 1]) {
        level--;
      }
    }
  }

  bool contains(const T& value) const {
    Node* current = head.get();

    for (int i = level - 1; i >= 0; i--) {
      while (current->forward[i] && comp(current->forward[i]->value, value)) {
        current = current->forward[i].get();
      }
    }

    current = current->forward[0].get();
    return current && !comp(current->value, value) && !comp(value, current->value);
  }

  bool empty() const {
    return !head->forward[0];
  }
};

// Splay Tree
template <typename K, typename V, typename Compare>
class splay_tree {
private:
  struct Node {
    K key;
    V value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr) {}
  };

  std::unique_ptr<Node> root;
  Compare comp;

  std::unique_ptr<Node> right_rotate(std::unique_ptr<Node> x) {
    std::unique_ptr<Node> y = std::move(x->left);
    x->left = std::move(y->right);
    y->right = std::move(x);
    return y;
  }

  std::unique_ptr<Node> left_rotate(std::unique_ptr<Node> x) {
    std::unique_ptr<Node> y = std::move(x->right);
    x->right = std::move(y->left);
    y->left = std::move(x);
    return y;
  }

  std::unique_ptr<Node> splay(std::unique_ptr<Node> node, const K& key) {
    if (!node) {
      return nullptr;
    }

    if (comp(key, node->key)) {
      if (!node->left) {
        return node;
      }

      if (comp(key, node->left->key)) {
        node->left->left = splay(std::move(node->left->left), key);
        node = right_rotate(std::move(node));
      } else if (comp(node->left->key, key)) {
        node->left->right = splay(std::move(node->left->right), key);
        if (node->left->right) {
          node->left = left_rotate(std::move(node->left));
        }
      }

      return node->left ? right_rotate(std::move(node)) : node;
    } else if (comp(node->key, key)) {
      if (!node->right) {
        return node;
      }

      if (comp(key, node->right->key)) {
        node->right->left = splay(std::move(node->right->left), key);
        if (node->right->left) {
          node->right = right_rotate(std::move(node->right));
        }
      } else if (comp(node->right->key, key)) {
        node->right->right = splay(std::move(node->right->right), key);
        node = left_rotate(std::move(node));
      }

      return node->right ? left_rotate(std::move(node)) : node;
    } else {
      return node;
    }
  }

public:
  splay_tree() : root(nullptr), comp(Compare()) {}

  void insert(const K& key, const V& value) {
    if (!root) {
      root = std::make_unique<Node>(key, value);
      return;
    }

    root = splay(std::move(root), key);

    if (comp(key, root->key)) {
      auto new_node = std::make_unique<Node>(key, value);
      new_node->right = std::move(root);
      new_node->left = std::move(root->left);
      root->left = nullptr;
      root = std::move(new_node);
    } else if (comp(root->key, key)) {
      auto new_node = std::make_unique<Node>(key, value);
      new_node->left = std::move(root);
      new_node->right = std::move(root->right);
      root->right = nullptr;
      root = std::move(new_node);
    } else {
      root->value = value;
    }
  }

  void remove(const K& key) {
    if (!root) {
      return;
    }

    root = splay(std::move(root), key);

    if (comp(root->key, key) || comp(key, root->key)) {
      return;
    }

    if (!root->left) {
      root = std::move(root->right);
    } else {
      auto temp = std::move(root->left);
      temp = splay(std::move(temp), key);
      temp->right = std::move(root->right);
      root = std::move(temp);
    }
  }

  std::optional<V> find(const K& key) {
    if (!root) {
      return std::nullopt;
    }

    root = splay(std::move(root), key);

    if (comp(root->key, key) || comp(key, root->key)) {
      return std::nullopt;
    }

    return root->value;
  }

  bool empty() const {
    return !root;
  }
};

// Disjoint Set
template <typename T>
class disjoint_set {
private:
  std::unordered_map<T, T> parent;
  std::unordered_map<T, int> rank;

public:
  void make_set(const T& x) {
    if (parent.find(x) == parent.end()) {
      parent[x] = x;
      rank[x] = 0;
    }
  }

  T find(const T& x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  void union_sets(const T& x, const T& y) {
    T x_root = find(x);
    T y_root = find(y);

    if (x_root == y_root) {
      return;
    }

    if (rank[x_root] < rank[y_root]) {
      parent[x_root] = y_root;
    } else if (rank[x_root] > rank[y_root]) {
      parent[y_root] = x_root;
    } else {
      parent[y_root] = x_root;
      rank[x_root]++;
    }
  }

  bool is_connected(const T& x, const T& y) {
    return find(x) == find(y);
  }
};

// Graph
template <typename T, typename W = int>
class graph {
private:
  struct Edge {
    T destination;
    W weight;

    Edge(const T& dest, const W& w) : destination(dest), weight(w) {}
  };

  std::unordered_map<T, std::vector<Edge>> adj_list;

public:
  void add_vertex(const T& vertex) {
    if (adj_list.find(vertex) == adj_list.end()) {
      adj_list[vertex] = std::vector<Edge>();
    }
  }

  void add_edge(const T& source, const T& destination, const W& weight = 1) {
    add_vertex(source);
    add_vertex(destination);
    adj_list[source].emplace_back(destination, weight);
  }

  void add_undirected_edge(const T& source, const T& destination, const W& weight = 1) {
    add_edge(source, destination, weight);
    add_edge(destination, source, weight);
  }

  std::vector<T> bfs(const T& start) const {
    std::vector<T> result;
    std::unordered_set<T> visited;
    std::queue<T> q;

    if (adj_list.find(start) == adj_list.end()) {
      return result;
    }

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
      T current = q.front();
      q.pop();
      result.push_back(current);

      for (const Edge& edge : adj_list.at(current)) {
        if (visited.find(edge.destination) == visited.end()) {
          visited.insert(edge.destination);
          q.push(edge.destination);
        }
      }
    }

    return result;
  }

  std::vector<T> dfs(const T& start) const {
    std::vector<T> result;
    std::unordered_set<T> visited;
    std::stack<T> s;

    if (adj_list.find(start) == adj_list.end()) {
      return result;
    }

    s.push(start);

    while (!s.empty()) {
      T current = s.top();
      s.pop();

      if (visited.find(current) == visited.end()) {
        visited.insert(current);
        result.push_back(current);

        for (const Edge& edge : adj_list.at(current)) {
          if (visited.find(edge.destination) == visited.end()) {
            s.push(edge.destination);
          }
        }
      }
    }

    return result;
  }

  std::unordered_map<T, W> dijkstra(const T& start) const {
    std::unordered_map<T, W> distances;
    std::priority_queue<std::pair<W, T>, std::vector<std::pair<W, T>>, std::greater<>> pq;

    for (const auto& pair : adj_list) {
      distances[pair.first] = std::numeric_limits<W>::max();
    }

    if (distances.find(start) == distances.end()) {
      return distances;
    }

    distances[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
      auto [current_dist, current] = pq.top();
      pq.pop();

      if (current_dist > distances[current]) {
        continue;
      }

      for (const Edge& edge : adj_list.at(current)) {
        W new_dist = current_dist + edge.weight;
        if (new_dist < distances[edge.destination]) {
          distances[edge.destination] = new_dist;
          pq.emplace(new_dist, edge.destination);
        }
      }
    }

    return distances;
  }

  bool has_vertex(const T& vertex) const {
    return adj_list.find(vertex) != adj_list.end();
  }

  bool has_edge(const T& source, const T& destination) const {
    if (adj_list.find(source) == adj_list.end()) {
      return false;
    }

    for (const Edge& edge : adj_list.at(source)) {
      if (edge.destination == destination) {
        return true;
      }
    }

    return false;
  }
};

} // namespace DataStructures
} // namespace CPlusPlusPlus

#endif // CPLUSPLUSPLUS_DATASTRUCTURES_H
