//===- parallel_for.cpp ---------------------------------------------------===//
//
// LLVM 项目的一部分，根据 Apache License v2.0 许可证发布，并带有 LLVM 异常。
// 有关许可证信息，请参阅 https://llvm.org/LICENSE.txt
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ 并行 for 循环示例。
//
//===----------------------------------------------------------------------===

#include "CPlusPlusPlus/All.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "测试并行 for 循环..." << std::endl;
    
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {10, 20, 30, 40, 50};
    std::vector<int> result(a.size());
    
    std::cout << "向量 a: ";
    for (int x : a) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << "向量 b: ";
    for (int x : b) std::cout << x << " ";
    std::cout << std::endl;
    
    // 使用 zip 进行并行迭代
    for (auto [i, x, y] : zip(a, b)) {
        result[i] = x + y;
    }
    
    std::cout << "结果: ";
    for (int x : result) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
