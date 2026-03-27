//===- CPlusPlusPlus.h ----------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ core header file.
//
//===----------------------------------------------------------------------===//

#ifndef CPLUSPLUSPLUS_CPLUSPLUSPLUS_H
#define CPLUSPLUSPLUS_CPLUSPLUSPLUS_H

#include <optional>
#include <cstdint>
#include <functional>

// C+++ version information
#define CPLUSPLUSPLUS_VERSION_MAJOR 0
#define CPLUSPLUSPLUS_VERSION_MINOR 1
#define CPLUSPLUSPLUS_VERSION_PATCH 0

// C+++ features macros
#define CPLUSPLUSPLUS_HAS_LET_VAR 1
#define CPLUSPLUSPLUS_HAS_AUTO_OPTIONAL 1
#define CPLUSPLUSPLUS_HAS_CONTAINER_LITERALS 1
#define CPLUSPLUSPLUS_HAS_DEFER 1
#define CPLUSPLUSPLUS_HAS_ERROR_PROPAGATION 1
#define CPLUSPLUSPLUS_HAS_PIPE_OPERATOR 1
#define CPLUSPLUSPLUS_HAS_PATTERN_MATCHING 1
#define CPLUSPLUSPLUS_HAS_DEFAULT_ARG_PLACEHOLDER 1
#define CPLUSPLUSPLUS_HAS_PROPERTY 1
#define CPLUSPLUSPLUS_HAS_INTERFACE 1
#define CPLUSPLUSPLUS_HAS_PARALLEL_FOR 1

// Forward declarations for C+++ features
namespace CPlusPlusPlus {

// Better Random library
namespace Random {
  template <typename T>
  T rand_int(T min, T max);

  double rand_double(double min, double max);

  bool rand_bool(double prob);

  template <typename Container>
  std::optional<typename Container::value_type> rand_choice(const Container& container);

  template <typename Container>
  void shuffle(Container& container);

  template <typename Container>
  Container rand_sample(const Container& container, size_t n);

  void set_seed(uint64_t seed);

  double rand_normal(double mean, double stddev);

} // namespace Random

// High-level data structures
namespace DataStructures {
  // AVL Tree
  template <typename T, typename Compare = std::less<T>>
  class avl_tree;

  // Skip List
  template <typename T, typename Compare = std::less<T>>
  class skip_list;

  // Splay Tree
  template <typename K, typename V, typename Compare = std::less<K>>
  class splay_tree;

  // B Tree
  template <typename T, size_t Order = 4, typename Compare = std::less<T>>
  class b_tree;

  // B+ Tree
  template <typename K, typename V, size_t Order = 4, typename Compare = std::less<K>>
  class b_plus_tree;

  // Graph
  template <typename T, typename W = int>
  class graph;

  // Disjoint Set
  template <typename T>
  class disjoint_set;

  // Segment Tree
  template <typename T, typename Op = std::plus<T>>
  class segment_tree;

  // Trie
  template <typename T>
  class trie;

} // namespace DataStructures

// Utility functions
namespace Utils {
  // Zip function for parallel for loops
  template <typename... Containers>
  auto zip(Containers&&... containers);

} // namespace Utils

} // namespace CPlusPlusPlus

#endif // CPLUSPLUSPLUS_CPLUSPLUSPLUS_H
