# C+++ (C++ Plus Plus Plus)

C+++ 是 ISO C++ 的现代化扩展，添加了语法糖和增强的标准库功能，同时保持与 ISO C++ 的完全兼容性。

## 核心价值

### 对比原生 C++/Cpp20 的优势

| 特性     | C+++            | 原生 C++/Cpp20       | 优势               | <br />        |
| ------ | --------------- | ------------------ | ---------------- | :------------ |
| 类型推断   | `let`/`var`     | `auto`             | 更清晰的语义区分（不可变/可变） | <br />        |
| 可选类型   | `auto?`         | `std::optional`    | 更简洁的语法和错误传播      | <br />        |
| 资源管理   | `defer`         | RAII               | 更直观的资源清理方式       | <br />        |
| 错误传播   | `?` 运算符         | 手动检查               | 链式调用更简洁，减少嵌套     | <br />        |
| 函数链式调用 | `|>` 管道运算符      | 嵌套函数调用           | 更清晰的数据流，可读性更好 |
| 模式匹配   | `match` 语句      | `switch`           | 更强大的匹配能力，支持范围匹配  | <br />        |
| 并行迭代   | 多容器并行 for 循环    | 手动实现               | 更简洁的并行处理语法       | <br />        |
| 属性访问   | `@property`     | 手动编写 getter/setter | 减少样板代码，提高可维护性    | <br />        |
| 接口定义   | `interface`     | 纯虚基类               | 更清晰的接口语义         | <br />        |
| 随机数生成  | `Better Random` | `std::random`      | 更易用的 API，功能更丰富   | <br />        |
| 高级数据结构 | 内置 AVL 树、跳表等    | 第三方库               | 开箱即用，无需额外依赖      | <br />        |

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

## 版本兼容性

### 支持的 Clang 版本

- **最低版本**：Clang 11.0.0
- **推荐版本**：Clang 12.0.0 或更新版本

### 支持的 C++ 标准

- **最低标准**：C++17
- **推荐标准**：C++17 或 C++20

### 平台兼容性

- **Windows**：完全兼容
- **Linux**：完全兼容
- **macOS**：完全兼容

### 已知兼容场景

- 所有标准 C++17 代码
- 大部分 C++20 代码
- 与标准库和第三方库的集成

### 已知不兼容场景

- 某些 C++20 特性可能需要特殊处理
- 其他编译器（如 GCC、MSVC）不支持 C+++ 插件

## 许可证

C+++ 是 LLVM 项目的一部分，根据 Apache License v2.0 with LLVM Exceptions 许可证发布。

## 📚 相关文档
- [安装指南](./INSTALL.md)
- [常见问题](./FAQ.md)

## 5 分钟快速尝鲜

### 最小可运行示例

创建一个名为 `quickstart.cpp` 的文件：

```cpp
#include "CPlusPlusPlus/All.h"

int main() {
    // 基本类型推断
    let message = "Hello, C+++!";
    var count = 0;
    
    // 可选类型和错误传播
    auto? value = optional<int>(42);
    if (value) {
        count = *value;
    }
    
    // 资源管理
    defer {
        std::cout << "Cleanup done!" << std::endl;
    };
    
    // 管道运算符
    auto result = 5 |> [](int x) { return x * 2; } |> [](int x) { return x + 1; };
    
    // 模式匹配
    match (result) {
        case 10: std::cout << "Result is 10" << std::endl; break;
        case 11: std::cout << "Result is 11" << std::endl; break;
        default: std::cout << "Result is " << result << std::endl; break;
    }
    
    std::cout << message << " Count: " << count << std::endl;
    return 0;
}
```

### 编译命令

假设您已经构建了 C+++ 插件，并且插件位于 `bin` 目录中：

#### Windows

```cmd
clang++ -Xclang -load -Xclang bin\ClangCPlusPlusPlus.dll -I include -std=c++17 quickstart.cpp -o quickstart.exe
quickstart.exe
```

#### Linux/macOS

```bash
clang++ -Xclang -load -Xclang bin/libClangCPlusPlusPlus.so -I include -std=c++17 quickstart.cpp -o quickstart
./quickstart
```

## 贡献

欢迎贡献！
