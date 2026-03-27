//===- Lexer.cpp ----------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ lexer implementation for handling new keywords and operators.
//
//===----------------------------------------------------------------------===//

#include "clang/Lex/Lexer.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Basic/TokenKinds.h"
using namespace clang;

namespace CPlusPlusPlus {

// TODO: Implement lexer extensions for C+++ keywords and operators
// - let/var variables
// - auto? optional type
// - defer statement
// - ? error propagation operator
// - |> pipe operator
// - if let/while let pattern matching
// - _ default argument placeholder
// - @property annotation
// - interface keyword

} // namespace CPlusPlusPlus
