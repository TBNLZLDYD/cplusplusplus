//===- property.cpp -------------------------------------------------------===//
//
// LLVM 项目的一部分，根据 Apache License v2.0 许可证发布，并带有 LLVM 异常。
// 有关许可证信息，请参阅 https://llvm.org/LICENSE.txt
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ @property 示例。
//
//===----------------------------------------------------------------------===

#include "CPlusPlusPlus/All.h"
#include <iostream>
#include <string>

class Person {
public:
    @property(std::string) name;
    @property(int) age;
};

int main() {
    std::cout << "测试 @property..." << std::endl;
    
    Person p;
    p.setName("John Doe");
    p.setAge(30);
    
    std::cout << "姓名: " << p.getName() << std::endl;
    std::cout << "年龄: " << p.getAge() << std::endl;
    
    // 更新属性
    p.setName("Jane Smith");
    p.setAge(25);
    
    std::cout << "更新后的姓名: " << p.getName() << std::endl;
    std::cout << "更新后的年龄: " << p.getAge() << std::endl;
    
    return 0;
}
