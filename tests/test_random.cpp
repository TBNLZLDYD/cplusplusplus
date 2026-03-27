//===- test_random.cpp ---------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Test file for Better Random library.
//
//===----------------------------------------------------------------------===//

#include "CPlusPlusPlus/Random.h"
#include <iostream>
#include <vector>
#include <string>

using namespace CPlusPlusPlus::Random;

int main() {
  std::cout << "Testing Better Random library..." << std::endl;

  // Test set_seed
  set_seed(42);
  std::cout << "Seed set to 42" << std::endl;

  // Test rand_int
  int int_val = rand_int(1, 100);
  std::cout << "Random int (1-100): " << int_val << std::endl;
  assert(int_val >= 1 && int_val <= 100);

  // Test rand_double
  double double_val = rand_double(0.0, 1.0);
  std::cout << "Random double (0.0-1.0): " << double_val << std::endl;
  assert(double_val >= 0.0 && double_val < 1.0);

  // Test rand_bool
  bool bool_val = rand_bool(0.5);
  std::cout << "Random bool (50%): " << (bool_val ? "true" : "false") << std::endl;

  // Test rand_choice
  std::vector<int> vec = {1, 2, 3, 4, 5};
  auto choice = rand_choice(vec);
  if (choice) {
    std::cout << "Random choice from vector: " << *choice << std::endl;
    assert(std::find(vec.begin(), vec.end(), *choice) != vec.end());
  } else {
    std::cout << "Random choice failed (empty container)" << std::endl;
  }

  // Test shuffle
  std::vector<int> shuffle_vec = {1, 2, 3, 4, 5};
  std::cout << "Before shuffle: ";
  for (int i : shuffle_vec) std::cout << i << " ";
  std::cout << std::endl;
  
  shuffle(shuffle_vec);
  
  std::cout << "After shuffle: ";
  for (int i : shuffle_vec) std::cout << i << " ";
  std::cout << std::endl;

  // Test rand_sample
  std::vector<std::string> str_vec = {"apple", "banana", "cherry", "date", "elderberry"};
  auto sample = rand_sample(str_vec, 3);
  std::cout << "Random sample (3 elements): ";
  for (const std::string& s : sample) std::cout << s << " ";
  std::cout << std::endl;
  assert(sample.size() == 3);

  // Test rand_normal
  double normal_val = rand_normal(0.0, 1.0);
  std::cout << "Random normal (mean=0, stddev=1): " << normal_val << std::endl;

  std::cout << "All random tests passed!" << std::endl;
  return 0;
}
