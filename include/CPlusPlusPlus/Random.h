//===- Random.h -----------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ Better Random library header file.
//
//===----------------------------------------------------------------------===//

#ifndef CPLUSPLUSPLUS_RANDOM_H
#define CPLUSPLUSPLUS_RANDOM_H

#include <random>
#include <optional>
#include <algorithm>
#include <iterator>

namespace CPlusPlusPlus {
namespace Random {

// Global random engine
inline std::mt19937_64& get_random_engine() {
  static std::mt19937_64 engine(std::random_device{}());
  return engine;
}

// Set random seed
inline void set_seed(uint64_t seed) {
  get_random_engine().seed(seed);
}

// Generate random integer in [min, max]
template <typename T>
inline T rand_int(T min, T max) {
  std::uniform_int_distribution<T> dist(min, max);
  return dist(get_random_engine());
}

// Generate random double in [min, max)
inline double rand_double(double min = 0.0, double max = 1.0) {
  std::uniform_real_distribution<double> dist(min, max);
  return dist(get_random_engine());
}

// Generate random bool with given probability
inline bool rand_bool(double prob = 0.5) {
  std::bernoulli_distribution dist(prob);
  return dist(get_random_engine());
}

// Randomly select an element from container
// Returns std::optional<T> to handle empty container
template <typename Container>
inline std::optional<typename Container::value_type> rand_choice(const Container& container) {
  if (container.empty()) {
    return std::nullopt;
  }
  auto it = container.begin();
  std::advance(it, rand_int<size_t>(0, container.size() - 1));
  return *it;
}

// Shuffle container in place
template <typename Container>
inline void shuffle(Container& container) {
  std::shuffle(container.begin(), container.end(), get_random_engine());
}

// Random sample n elements from container without replacement
template <typename Container>
inline Container rand_sample(const Container& container, size_t n) {
  if (n >= container.size()) {
    return container;
  }
  
  Container result;
  std::copy(container.begin(), container.end(), std::back_inserter(result));
  shuffle(result);
  result.resize(n);
  return result;
}

// Generate random number from normal distribution
inline double rand_normal(double mean = 0.0, double stddev = 1.0) {
  std::normal_distribution<double> dist(mean, stddev);
  return dist(get_random_engine());
}

} // namespace Random
} // namespace CPlusPlusPlus

#endif // CPLUSPLUSPLUS_RANDOM_H
