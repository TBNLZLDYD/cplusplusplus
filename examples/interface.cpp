//===- interface.cpp ------------------------------------------------------===//
//
// LLVM 项目的一部分，根据 Apache License v2.0 许可证发布，并带有 LLVM 异常。
// 有关许可证信息，请参阅 https://llvm.org/LICENSE.txt
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ interface 示例。
//
//===----------------------------------------------------------------------===

#include "CPlusPlusPlus/All.h"
#include <iostream>

interface Drawable {
    void draw() const;
};

class Circle : public Drawable {
public:
    void draw() const override {
        std::cout << "绘制圆形" << std::endl;
    }
};

class Square : public Drawable {
public:
    void draw() const override {
        std::cout << "绘制正方形" << std::endl;
    }
};

void draw_shape(const Drawable& shape) {
    shape.draw();
}

int main() {
    std::cout << "测试 interface..." << std::endl;
    
    Circle circle;
    Square square;
    
    std::cout << "绘制圆形: ";
    draw_shape(circle);
    
    std::cout << "绘制正方形: ";
    draw_shape(square);
    
    return 0;
}
