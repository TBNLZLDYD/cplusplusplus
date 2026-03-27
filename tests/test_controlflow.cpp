//===- test_controlflow.cpp -----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Test file for control flow enhancements.
//
//===----------------------------------------------------------------------===//

#include "CPlusPlusPlus/ControlFlow.h"
#include <iostream>
#include <vector>

using namespace CPlusPlusPlus;

int main() {
  std::cout << "Testing control flow enhancements..." << std::endl;

  // Test DeferGuard
  std::cout << "Testing DeferGuard..." << std::endl;
  
  std::vector<int> vec;
  
  {
    DeferGuard guard([&vec]() {
      std::cout << "DeferGuard executed: cleaning up..." << std::endl;
      vec.clear();
    });
    
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    std::cout << "Inside scope: vector size = " << vec.size() << std::endl;
  }
  
  std::cout << "Outside scope: vector size = " << vec.size() << std::endl;
  assert(vec.empty() == true);
  
  // Test multiple DeferGuard objects
  std::cout << "\nTesting multiple DeferGuard objects..." << std::endl;
  
  int a = 0, b = 0;
  
  {
    DeferGuard guard1([&a]() {
      std::cout << "DeferGuard 1 executed: a = " << ++a << std::endl;
    });
    
    DeferGuard guard2([&b]() {
      std::cout << "DeferGuard 2 executed: b = " << ++b << std::endl;
    });
    
    std::cout << "Inside scope: a = " << a << ", b = " << b << std::endl;
  }
  
  std::cout << "Outside scope: a = " << a << ", b = " << b << std::endl;
  assert(a == 1 && b == 1);
  
  std::cout << "\nAll control flow tests passed!" << std::endl;
  return 0;
}
