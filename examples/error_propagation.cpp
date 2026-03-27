//===- error_propagation.cpp ----------------------------------------------===//
//
// LLVM 项目的一部分，根据 Apache License v2.0 许可证发布，并带有 LLVM 异常。
// 有关许可证信息，请参阅 https://llvm.org/LICENSE.txt
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ 错误传播示例。
//
//===----------------------------------------------------------------------===

#include "CPlusPlusPlus/All.h"
#include <iostream>

optional<int> divide(int a, int b) {
    if (b == 0) {
        std::cout << "错误: 除零" << std::endl;
        return nullopt;
    }
    return a / b;
}

optional<int> add_one(optional<int> value) {
    if (!value) return nullopt;
    return *value + 1;
}

int main() {
    std::cout << "测试错误传播..." << std::endl;
    
    // 成功情况
    auto result1 = divide(10, 2) ? add_one(*result1) ? *result1 : 0;
    std::cout << "10 / 2 + 1 = " << result1 << std::endl;
    
    // 失败情况 (除零)
    auto result2 = divide(10, 0) ? add_one(*result2) ? *result2 : 0;
    std::cout << "10 / 0 + 1 = " << result2 << std::endl;
    
    return 0;
}
