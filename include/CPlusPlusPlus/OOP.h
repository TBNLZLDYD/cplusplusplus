//===- OOP.h --------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ object-oriented programming enhancements header file.
//
//===----------------------------------------------------------------------===//

#ifndef CPLUSPLUSPLUS_OOP_H
#define CPLUSPLUSPLUS_OOP_H

namespace CPlusPlusPlus {

// Property attribute helper
// Note: This is a placeholder for compiler-generated property implementation
struct PropertyAttribute {
  bool readonly = false;
};

// Interface base class
// Note: This is a placeholder for compiler-generated interface implementation
class InterfaceBase {
public:
  virtual ~InterfaceBase() = default;
  InterfaceBase(const InterfaceBase&) = delete;
  InterfaceBase& operator=(const InterfaceBase&) = delete;
protected:
  InterfaceBase() = default;
};

// Property macro for manual use
#define CPLUSPLUSPLUS_PROPERTY(type, name) \
private: \
  type name##_; \
public: \
  type get_##name() const { return name##_; } \
  void set_##name(type value) { name##_ = value; }

// Readonly property macro
#define CPLUSPLUSPLUS_PROPERTY_READONLY(type, name) \
private: \
  type name##_; \
public: \
  type get_##name() const { return name##_; }

// Interface macro for manual use
#define CPLUSPLUSPLUS_INTERFACE(name) \
class name : public CPlusPlusPlus::InterfaceBase

} // namespace CPlusPlusPlus

#endif // CPLUSPLUSPLUS_OOP_H
