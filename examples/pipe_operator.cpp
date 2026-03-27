//===- pipe_operator.cpp ---------------------------------------------------===//
//
// LLVM 项目的一部分，根据 Apache License v2.0 许可证发布，并带有 LLVM 异常。
// 有关许可证信息，请参阅 https://llvm.org/LICENSE.txt
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ 管道运算符示例。
//
//===----------------------------------------------------------------------===

#include "CPlusPlusPlus/All.h"
#include <iostream>

int square(int x) {
    return x * x;
}

int add_one(int x) {
    return x + 1;
}

int multiply_by_two(int x) {
    return x * 2;
}

int main() {
    std::cout << "测试管道运算符..." << std::endl;
    
    // 使用管道运算符进行函数链式调用
    auto result = 5 |> square |> add_one |> multiply_by_two;
    std::cout << "5 |> square |> add_one |> multiply_by_two = " << result << std::endl;
    
    // 等效于: multiply_by_two(add_one(square(5)))
    auto equivalent = multiply_by_two(add_one(square(5)));
    std::cout << "等效: multiply_by_two(add_one(square(5))) = " << equivalent << std::endl;
    
    return 0;
}
