# C+++ (C++ Plus Plus Plus)

C+++ 是 ISO C++ 的现代化扩展，添加了语法糖和增强的标准库功能，同时保持与 ISO C++ 的完全兼容性。

## 特性

### 语法糖
- `let` 和 `var` 用于类型推断
- `auto?` 用于可选类型
- `defer` 语句用于资源管理
- 使用 `?` 运算符进行错误传播
- 管道运算符 `|>` 用于函数链式调用
- 使用 `match` 语句进行模式匹配
- 多容器并行 for 循环
- `@property` 用于自动生成 getter/setter
- `interface` 用于纯虚基类

### 增强标准库
- **Better Random**：易用的随机数生成
- **高级数据结构**：AVL树、跳表、图、并查集
- **容器增强**：`zip` 函数用于并行迭代
- **控制流**：`defer` 实现、错误传播工具

## 安装

### 先决条件
- Clang 11.0.0 或更新版本
- CMake 3.10 或更新版本
- 兼容 C++17 的编译器

### 构建说明

1. 克隆 LLVM/Clang 仓库：
   ```bash
   git clone https://github.com/llvm/llvm-project.git
   cd llvm-project
   ```

2. 创建构建目录：
   ```bash
   mkdir build
   cd build
   ```

3. 配置 CMake：
   ```bash
   cmake -DLLVM_ENABLE_PROJECTS=clang ..
   ```

4. 构建 C+++ 插件：
   ```bash
   cmake --build . --config Release --target ClangCPlusPlusPlus
   ```

5. 插件将构建为 `ClangCPlusPlusPlus.dll`（Windows）或 `libClangCPlusPlusPlus.so`（Linux）。

## 使用

### 使用 C+++ 插件编译

要编译 C+++ 文件，请使用 Clang 并通过 `-Xclang -load` 选项加载插件：

```bash
clang++ -Xclang -load -Xclang /path/to/ClangCPlusPlusPlus.dll -I /path/to/CPlusPlusPlus/include -std=c++17 your_file.cpp
```

### 启用特性

您可以使用预处理指令启用或禁用特定特性：

```cpp
#define CPLUSPLUSPLUS_ENABLE_LET_VAR 1       // 启用 let/var
#define CPLUSPLUSPLUS_ENABLE_AUTO_OPTIONAL 1 // 启用 auto?
#define CPLUSPLUSPLUS_ENABLE_DEFER 1         // 启用 defer
#define CPLUSPLUSPLUS_ENABLE_ERROR_PROP 1    // 启用错误传播
#define CPLUSPLUSPLUS_ENABLE_PIPE 1          // 启用管道运算符
#define CPLUSPLUSPLUS_ENABLE_MATCH 1         // 启用模式匹配
#define CPLUSPLUSPLUS_ENABLE_PARALLEL_FOR 1  // 启用并行 for
#define CPLUSPLUSPLUS_ENABLE_PROPERTY 1      // 启用 @property
#define CPLUSPLUSPLUS_ENABLE_INTERFACE 1     // 启用 interface

#include "CPlusPlusPlus/All.h"
```

## 示例

### 基本语法糖

```cpp
#include "CPlusPlusPlus/All.h"

int main() {
    // let (不可变)
    let x = 42; // int
    
    // var (可变)
    var y = 3.14; // double
    y = 2.718;
    
    // auto? (可选类型)
    auto? z = optional<int>(42);
    if (z) {
        // z 有值
    }
    
    // defer
    defer {
        // 这段代码将在当前作用域退出时运行
    };
    
    return 0;
}
```

### 错误传播

```cpp
#include "CPlusPlusPlus/All.h"

optional<int> divide(int a, int b) {
    if (b == 0) return nullopt;
    return a / b;
}

int main() {
    auto result = divide(10, 2) ? divide(*result, 2) ? *result : 0;
    // result = 2
    return 0;
}
```

### 管道运算符

```cpp
#include "CPlusPlusPlus/All.h"

int square(int x) { return x * x; }
int add_one(int x) { return x + 1; }

int main() {
    auto result = 5 |> square |> add_one;
    // result = 26
    return 0;
}
```

### 模式匹配

```cpp
#include "CPlusPlusPlus/All.h"

int main() {
    int value = 42;
    match (value) {
        case 0: // 处理零
            break;
        case 1 ... 10: // 处理 1-10
            break;
        default: // 处理其他情况
            break;
    }
    return 0;
}
```

### 并行 For 循环

```cpp
#include "CPlusPlusPlus/All.h"

int main() {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {4, 5, 6};
    std::vector<int> result(a.size());
    
    for (auto [i, x, y] : zip(a, b)) {
        result[i] = x + y;
    }
    // result = {5, 7, 9}
    return 0;
}
```

### @property

```cpp
#include "CPlusPlusPlus/All.h"

class Person {
public:
    @property(std::string) name;
    @property(int) age;
};

int main() {
    Person p;
    p.setName("John");
    p.setAge(30);
    std::cout << p.getName() << " is " << p.getAge() << " years old." << std::endl;
    return 0;
}
```

### Interface

```cpp
#include "CPlusPlusPlus/All.h"

interface Drawable {
    void draw() const;
};

class Circle : public Drawable {
public:
    void draw() const override {
        // 绘制圆形
    }
};

int main() {
    Drawable* d = new Circle();
    d->draw();
    delete d;
    return 0;
}
```

### Better Random

```cpp
#include "CPlusPlusPlus/All.h"

int main() {
    // 设置种子
    Random::set_seed(42);
    
    // 生成随机值
    int rint = Random::rand_int(1, 100);
    double rdouble = Random::rand_double();
    bool rbool = Random::rand_bool();
    
    // 打乱向量
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Random::shuffle(vec);
    
    // 随机选择元素
    auto choice = Random::rand_choice(vec);
    if (choice) {
        // 使用 *choice
    }
    
    return 0;
}
```

### 高级数据结构

```cpp
#include "CPlusPlusPlus/All.h"

int main() {
    // AVL 树
    DataStructures::avl_tree<int> avl;
    avl.insert(50);
    avl.insert(30);
    avl.insert(70);
    bool found = avl.contains(30);
    
    // 图
    DataStructures::graph<int> g;
    g.add_undirected_edge(1, 2);
    g.add_undirected_edge(2, 3);
    auto bfs_result = g.bfs(1);
    
    // 并查集
    DataStructures::disjoint_set<int> ds;
    ds.make_set(1);
    ds.make_set(2);
    ds.union_sets(1, 2);
    bool connected = ds.is_connected(1, 2);
    
    return 0;
}
```

## 兼容性

- **ISO C++ 兼容性**：当不使用插件时，所有 C+++ 代码都是有效的 ISO C++ 代码
- **Clang 版本**：需要 Clang 11.0.0 或更新版本
- **平台**：Windows、Linux、macOS

## 许可证

C+++ 是 LLVM 项目的一部分，根据 Apache License v2.0 with LLVM Exceptions 许可证发布。

## 贡献

欢迎贡献！请参阅 LLVM 项目的贡献指南了解更多信息。
