//===- Container.h --------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ container and iteration enhancements header file.
//
//===----------------------------------------------------------------------===//

#ifndef CPLUSPLUSPLUS_CONTAINER_H
#define CPLUSPLUSPLUS_CONTAINER_H

#include <tuple>
#include <iterator>
#include <vector>
#include <array>
#include <map>
#include <initializer_list>

namespace CPlusPlusPlus {
namespace Utils {

// Zip function for parallel for loops
template <typename... Containers>
class ZipIterator {
private:
  std::tuple<typename Containers::iterator...> iterators;
  std::tuple<typename Containers::iterator...> end_iterators;

  template <size_t... Is>
  bool all_equal(bool first, std::index_sequence<Is...>) {
    return (first && ... && (std::get<Is>(iterators) == std::get<Is>(end_iterators)));
  }

  template <size_t... Is>
  void increment(std::index_sequence<Is...>) {
    (++std::get<Is>(iterators), ...);
  }

  template <size_t... Is>
  auto dereference(std::index_sequence<Is...>) {
    return std::make_tuple(*std::get<Is>(iterators)...);
  }

public:
  using difference_type = std::ptrdiff_t;
  using value_type = std::tuple<typename Containers::value_type...>;
  using pointer = value_type*;
  using reference = value_type;
  using iterator_category = std::input_iterator_tag;

  ZipIterator(typename Containers::iterator... its, typename Containers::iterator... ends)
      : iterators(its...), end_iterators(ends...) {}

  bool operator==(const ZipIterator& other) const {
    return all_equal(true, std::index_sequence_for<Containers...>{});
  }

  bool operator!=(const ZipIterator& other) const {
    return !(*this == other);
  }

  ZipIterator& operator++() {
    increment(std::index_sequence_for<Containers...>{});
    return *this;
  }

  ZipIterator operator++(int) {
    ZipIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  value_type operator*() const {
    return dereference(std::index_sequence_for<Containers...>{});
  }
};

template <typename... Containers>
class ZipView {
private:
  std::tuple<Containers&...> containers;

  template <size_t... Is>
  auto begin_impl(std::index_sequence<Is...>) {
    return ZipIterator<Containers...>(std::begin(std::get<Is>(containers))..., std::end(std::get<Is>(containers))...);
  }

  template <size_t... Is>
  auto end_impl(std::index_sequence<Is...>) {
    return ZipIterator<Containers...>(std::end(std::get<Is>(containers))..., std::end(std::get<Is>(containers))...);
  }

public:
  ZipView(Containers&... conts) : containers(conts...) {}

  auto begin() {
    return begin_impl(std::index_sequence_for<Containers...>{});
  }

  auto end() {
    return end_impl(std::index_sequence_for<Containers...>{});
  }
};

// Zip function
template <typename... Containers>
auto zip(Containers&&... containers) {
  return ZipView<Containers...>(containers...);
}

} // namespace Utils

// Container literal helpers
namespace Detail {
  // Helper for map literal syntax
  template <typename K, typename V>
  std::map<K, V> make_map(std::initializer_list<std::pair<K, V>> init) {
    return std::map<K, V>(init);
  }

  // Helper for array literal syntax
  template <typename T, size_t N>
  std::array<T, N> make_array(std::initializer_list<T> init) {
    std::array<T, N> arr;
    std::copy(init.begin(), init.end(), arr.begin());
    return arr;
  }
}

} // namespace CPlusPlusPlus

#endif // CPLUSPLUSPLUS_CONTAINER_H
