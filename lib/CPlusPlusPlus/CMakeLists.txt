add_llvm_library(ClangCPlusPlusPlus SHARED
  CPlusPlusPlus.cpp
  Lexer.cpp
  Parser.cpp
  Transformer.cpp
  
  LINK_LIBS
  clangAST
  clangBasic
  clangFrontend
  clangLex
  clangParse
  clangSema
  
  DEPENDS
  clangAST
  clangBasic
  clangFrontend
  clangLex
  clangParse
  clangSema
)
