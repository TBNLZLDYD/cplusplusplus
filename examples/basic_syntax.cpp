//===- basic_syntax.cpp ---------------------------------------------------===//
//
// LLVM 项目的一部分，根据 Apache License v2.0 许可证发布，并带有 LLVM 异常。
// 有关许可证信息，请参阅 https://llvm.org/LICENSE.txt
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ 基本语法糖示例。
//
//===----------------------------------------------------------------------===

#include "CPlusPlusPlus/All.h"
#include <iostream>

int main() {
    std::cout << "测试 C+++ 基本语法..." << std::endl;
    
    // let (不可变)
    let x = 42; // int
    std::cout << "let x = " << x << std::endl;
    
    // var (可变)
    var y = 3.14; // double
    std::cout << "var y = " << y << std::endl;
    y = 2.718;
    std::cout << "y 修改后 = " << y << std::endl;
    
    // auto? (可选类型)
    auto? z = optional<int>(42);
    if (z) {
        std::cout << "auto? z 有值: " << *z << std::endl;
    }
    
    // defer
    std::cout << "defer 之前" << std::endl;
    defer {
        std::cout << "defer 代码执行" << std::endl;
    };
    std::cout << "defer 声明之后" << std::endl;
    
    return 0;
}
