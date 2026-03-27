//===- random.cpp ---------------------------------------------------------===//
//
// LLVM 项目的一部分，根据 Apache License v2.0 许可证发布，并带有 LLVM 异常。
// 有关许可证信息，请参阅 https://llvm.org/LICENSE.txt
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ Better Random 库示例。
//
//===----------------------------------------------------------------------===

#include "CPlusPlusPlus/All.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "测试 Better Random 库..." << std::endl;
    
    // 设置种子以确保可重现性
    Random::set_seed(42);
    std::cout << "种子设置为 42" << std::endl;
    
    // 生成随机整数
    std::cout << "随机整数 (1-10): " << Random::rand_int(1, 10) << std::endl;
    std::cout << "随机整数 (100-200): " << Random::rand_int(100, 200) << std::endl;
    
    // 生成随机浮点数
    std::cout << "随机浮点数 (0-1): " << Random::rand_double() << std::endl;
    std::cout << "随机浮点数 (1-5): " << Random::rand_double(1.0, 5.0) << std::endl;
    
    // 生成随机布尔值
    std::cout << "随机布尔值: " << (Random::rand_bool() ? "true" : "false") << std::endl;
    
    // 打乱向量
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "原始向量: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    Random::shuffle(vec);
    std::cout << "打乱后的向量: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
    
    // 随机选择元素
    auto choice = Random::rand_choice(vec);
    if (choice) {
        std::cout << "从向量中随机选择: " << *choice << std::endl;
    }
    
    return 0;
}
