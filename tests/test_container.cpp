//===- test_container.cpp -------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Test file for container enhancements.
//
//===----------------------------------------------------------------------===//

#include "CPlusPlusPlus/Container.h"
#include <iostream>
#include <vector>
#include <string>

using namespace CPlusPlusPlus::Utils;

int main() {
  std::cout << "Testing container enhancements..." << std::endl;

  // Test zip function
  std::cout << "Testing zip function..." << std::endl;
  
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  std::vector<std::string> names = {"one", "two", "three", "four", "five"};
  std::vector<double> values = {1.1, 2.2, 3.3, 4.4, 5.5};
  
  std::cout << "Zipping three vectors: " << std::endl;
  for (const auto& tuple : zip(numbers, names, values)) {
    int num = std::get<0>(tuple);
    std::string name = std::get<1>(tuple);
    double value = std::get<2>(tuple);
    std::cout << "Num: " << num << ", Name: " << name << ", Value: " << value << std::endl;
  }
  
  // Test zip with different container sizes
  std::cout << "\nTesting zip with different container sizes..." << std::endl;
  std::vector<int> short_vec = {1, 2, 3};
  std::vector<std::string> long_vec = {"a", "b", "c", "d", "e"};
  
  std::cout << "Zipping vectors of different sizes: " << std::endl;
  int count = 0;
  for (const auto& tuple : zip(short_vec, long_vec)) {
    int num = std::get<0>(tuple);
    std::string str = std::get<1>(tuple);
    std::cout << "Num: " << num << ", Str: " << str << std::endl;
    count++;
  }
  std::cout << "Total pairs: " << count << " (should be 3)" << std::endl;
  assert(count == 3);
  
  std::cout << "\nAll container tests passed!" << std::endl;
  return 0;
}
