//===- test_oop.cpp -------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Test file for object-oriented programming enhancements.
//
//===----------------------------------------------------------------------===//

#include "CPlusPlusPlus/OOP.h"
#include <iostream>
#include <string>

using namespace CPlusPlusPlus;

// Test property macro
class TestClass {
public:
  CPLUSPLUSPLUS_PROPERTY(int, value);
  CPLUSPLUSPLUS_PROPERTY_READONLY(std::string, name);
  
  TestClass(int v, const std::string& n) {
    value_ = v;
    name_ = n;
  }
};

// Test interface macro
CPLUSPLUSPLUS_INTERFACE(TestInterface) {
public:
  virtual void doSomething() = 0;
  virtual int getValue() = 0;
};

// Implement the interface
class TestImplementation : public TestInterface {
private:
  int value;
public:
  TestImplementation(int v) : value(v) {}
  
  void doSomething() override {
    std::cout << "TestImplementation::doSomething() called" << std::endl;
  }
  
  int getValue() override {
    return value;
  }
};

int main() {
  std::cout << "Testing object-oriented programming enhancements..." << std::endl;

  // Test property macro
  std::cout << "Testing property macro..." << std::endl;
  TestClass obj(42, "Test");
  
  std::cout << "Initial value: " << obj.get_value() << std::endl;
  std::cout << "Initial name: " << obj.get_name() << std::endl;
  
  obj.set_value(100);
  std::cout << "After set_value(100): " << obj.get_value() << std::endl;
  assert(obj.get_value() == 100);
  
  // Test interface
  std::cout << "\nTesting interface..." << std::endl;
  TestImplementation impl(50);
  TestInterface& iface = impl;
  
  iface.doSomething();
  std::cout << "Interface getValue(): " << iface.getValue() << std::endl;
  assert(iface.getValue() == 50);
  
  std::cout << "\nAll OOP tests passed!" << std::endl;
  return 0;
}
