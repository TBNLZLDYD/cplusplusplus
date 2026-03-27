//===- pattern_matching.cpp ------------------------------------------------===//
//
// LLVM 项目的一部分，根据 Apache License v2.0 许可证发布，并带有 LLVM 异常。
// 有关许可证信息，请参阅 https://llvm.org/LICENSE.txt
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ 模式匹配示例。
//
//===----------------------------------------------------------------------===

#include "CPlusPlusPlus/All.h"
#include <iostream>

int main() {
    std::cout << "测试模式匹配..." << std::endl;
    
    int value = 42;
    std::cout << "匹配值: " << value << std::endl;
    
    match (value) {
        case 0:
            std::cout << "Case 0: 零" << std::endl;
            break;
        case 1 ... 10:
            std::cout << "Case 1-10: 小数字" << std::endl;
            break;
        case 11 ... 100:
            std::cout << "Case 11-100: 中数字" << std::endl;
            break;
        default:
            std::cout << "Default case: 大数字" << std::endl;
            break;
    }
    
    return 0;
}
