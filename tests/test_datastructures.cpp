//===- test_datastructures.cpp --------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Test file for high-level data structures.
//
//===----------------------------------------------------------------------===//

#include "CPlusPlusPlus/DataStructures.h"
#include <iostream>
#include <vector>
#include <string>

using namespace CPlusPlusPlus::DataStructures;

int main() {
  std::cout << "Testing high-level data structures..." << std::endl;

  // Test AVL Tree
  std::cout << "\nTesting AVL Tree..." << std::endl;
  avl_tree<int> avl;
  
  // Insert elements
  avl.insert(10);
  avl.insert(20);
  avl.insert(5);
  avl.insert(15);
  avl.insert(25);
  
  std::cout << "AVL tree height: " << avl.height() << std::endl;
  
  // Test contains
  assert(avl.contains(10) == true);
  assert(avl.contains(100) == false);
  std::cout << "AVL tree contains 10: " << (avl.contains(10) ? "true" : "false") << std::endl;
  std::cout << "AVL tree contains 100: " << (avl.contains(100) ? "true" : "false") << std::endl;
  
  // Test remove
  avl.remove(10);
  assert(avl.contains(10) == false);
  std::cout << "AVL tree contains 10 after removal: " << (avl.contains(10) ? "true" : "false") << std::endl;
  
  // Test Disjoint Set
  std::cout << "\nTesting Disjoint Set..." << std::endl;
  disjoint_set<int> ds;
  
  // Make sets
  ds.make_set(1);
  ds.make_set(2);
  ds.make_set(3);
  ds.make_set(4);
  ds.make_set(5);
  
  // Union sets
  ds.union_sets(1, 2);
  ds.union_sets(3, 4);
  ds.union_sets(1, 3);
  
  // Test connected
  assert(ds.is_connected(1, 4) == true);
  assert(ds.is_connected(1, 5) == false);
  std::cout << "1 and 4 are connected: " << (ds.is_connected(1, 4) ? "true" : "false") << std::endl;
  std::cout << "1 and 5 are connected: " << (ds.is_connected(1, 5) ? "true" : "false") << std::endl;
  
  // Test Graph
  std::cout << "\nTesting Graph..." << std::endl;
  graph<int> g;
  
  // Add edges
  g.add_undirected_edge(1, 2, 1);
  g.add_undirected_edge(1, 3, 2);
  g.add_undirected_edge(2, 4, 3);
  g.add_undirected_edge(3, 4, 4);
  g.add_undirected_edge(4, 5, 5);
  
  // Test BFS
  std::cout << "BFS starting from 1: ";
  auto bfs_result = g.bfs(1);
  for (int node : bfs_result) {
    std::cout << node << " ";
  }
  std::cout << std::endl;
  
  // Test DFS
  std::cout << "DFS starting from 1: ";
  auto dfs_result = g.dfs(1);
  for (int node : dfs_result) {
    std::cout << node << " ";
  }
  std::cout << std::endl;
  
  // Test Dijkstra
  std::cout << "Dijkstra distances from 1: " << std::endl;
  auto distances = g.dijkstra(1);
  for (const auto& pair : distances) {
    std::cout << "Distance to " << pair.first << ": " << pair.second << std::endl;
  }
  
  std::cout << "\nAll data structure tests passed!" << std::endl;
  return 0;
}
