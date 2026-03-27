//===- Features.cpp -------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ features implementation file.
//
//===----------------------------------------------------------------------===//

#include "CPlusPlusPlus.h"
#include "ControlFlow.h"
#include "OOP.h"
#include "Container.h"
#include "Random.h"
#include <random>
#include <algorithm>
#include <vector>

namespace CPlusPlusPlus {

// Better Random library implementation
namespace Random {
  static std::mt19937_64 rng(std::random_device{}());

  template <typename T>
  T rand_int(T min, T max) {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(rng);
  }

  double rand_double(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
  }

  bool rand_bool(double prob) {
    std::bernoulli_distribution dist(prob);
    return dist(rng);
  }

  template <typename Container>
  std::optional<typename Container::value_type> rand_choice(const Container& container) {
    if (container.empty()) {
      return std::nullopt;
    }
    auto it = container.begin();
    std::advance(it, rand_int<size_t>(0, container.size() - 1));
    return *it;
  }

  template <typename Container>
  void shuffle(Container& container) {
    std::shuffle(container.begin(), container.end(), rng);
  }

  template <typename Container>
  Container rand_sample(const Container& container, size_t n) {
    if (n >= container.size()) {
      return container;
    }
    
    std::vector<typename Container::value_type> temp(container.begin(), container.end());
    std::shuffle(temp.begin(), temp.end(), rng);
    temp.resize(n);
    
    return Container(temp.begin(), temp.end());
  }

  void set_seed(uint64_t seed) {
    rng.seed(seed);
  }

  double rand_normal(double mean, double stddev) {
    std::normal_distribution<double> dist(mean, stddev);
    return dist(rng);
  }

  // Explicit instantiations
  template int rand_int(int, int);
  template long rand_int(long, long);
  template long long rand_int(long long, long long);
  template unsigned int rand_int(unsigned int, unsigned int);
  template unsigned long rand_int(unsigned long, unsigned long);
  template unsigned long long rand_int(unsigned long long, unsigned long long);

  template std::optional<int> rand_choice(const std::vector<int>&);
  template std::optional<double> rand_choice(const std::vector<double>&);
  template std::optional<std::string> rand_choice(const std::vector<std::string>&);

  template void shuffle(std::vector<int>&);
  template void shuffle(std::vector<double>&);
  template void shuffle(std::vector<std::string>&);

  template std::vector<int> rand_sample(const std::vector<int>&, size_t);
  template std::vector<double> rand_sample(const std::vector<double>&, size_t);
  template std::vector<std::string> rand_sample(const std::vector<std::string>&, size_t);

} // namespace Random

// High-level data structures are defined in DataStructures.h

} // namespace CPlusPlusPlus