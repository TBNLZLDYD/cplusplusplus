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
#include "clang/Basic/IdentifierTable.h"
using namespace clang;

namespace CPlusPlusPlus {

// C+++ keywords
static const char* const CPlusPlusPlusKeywords[] = {
  "let",
  "var",
  "defer",
  "match",
  "interface",
  nullptr
};

// Register C+++ keywords
void registerKeywords(IdentifierTable &IdentTable) {
  for (const char* const* KW = CPlusPlusPlusKeywords; *KW; ++KW) {
    IdentTable.get(*KW).setIsKeyword(true);
  }
}

// Handle C+++ operators
TokenKind getOperatorKind(const char* Op, unsigned Length) {
  if (Length == 2) {
    if (Op[0] == '|' && Op[1] == '>')
      return tok::pipe_operator; // Custom token for pipe operator
    if (Op[0] == '?' && Op[1] == '?')
      return tok::question_question; // Custom token for error propagation
  }
  return tok::unknown;
}

} // namespace CPlusPlusPlus