# C+++ 使用手册

## 快速开始

### 1. 基本编译

```bash
# 最简单的编译命令
clang++ -Xclang -load -Xclang ClangCPlusPlusPlus.dll -I include -std=c++17 your_file.cpp
```

### 2. 启用/禁用特性

```cpp
// 在包含头文件之前定义宏来启用/禁用特性
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

## 特性详解

### 1. let/var - 类型推断

```cpp
let x = 42;        // x 是 const int
var y = 3.14;      // y 是 double，可以修改
```

### 2. auto? - 可选类型

```cpp
auto? maybe_value = some_function();
if (maybe_value) {
    // 使用 *maybe_value 访问值
    std::cout << *maybe_value << std::endl;
}
```

### 3. defer - 延迟执行

```cpp
void process_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    defer {
        fclose(file);  // 函数退出时自动执行
    };
    
    // 处理文件...
}  // file 自动关闭
```

### 4. 错误传播 ?

```cpp
optional<int> divide(int a, int b) {
    if (b == 0) return nullopt;
    return a / b;
}

// 使用 ? 运算符传播错误
auto result = divide(10, 2) ? divide(*result, 2) ? *result : 0;
```

### 5. 管道运算符 |>

```cpp
int square(int x) { return x * x; }
int add_one(int x) { return x + 1; }

// 传统写法
auto result = add_one(square(5));  // 26

// 管道写法
auto result = 5 |> square |> add_one;  // 26
```

### 6. 模式匹配 match

```cpp
int value = 42;
match (value) {
    case 0:
        std::cout << "零" << std::endl;
        break;
    case 1 ... 10:
        std::cout << "小数字" << std::endl;
        break;
    case 11 ... 100:
        std::cout << "中数字" << std::endl;
        break;
    default:
        std::cout << "大数字" << std::endl;
        break;
}
```

### 7. 并行 for 循环

```cpp
std::vector<int> a = {1, 2, 3};
std::vector<int> b = {4, 5, 6};

for (auto [i, x, y] : zip(a, b)) {
    std::cout << i << ": " << x << " + " << y << " = " << (x + y) << std::endl;
}
```

### 8. @property

```cpp
class Person {
public:
    @property(std::string) name;
    @property(int) age;
};

Person p;
p.setName("张三");
p.setAge(25);
std::cout << p.getName() << " 今年 " << p.getAge() << " 岁" << std::endl;
```

### 9. interface

```cpp
interface Drawable {
    void draw() const;
};

class Circle : public Drawable {
public:
    void draw() const override {
        std::cout << "绘制圆形" << std::endl;
    }
};
```

## Better Random 库

```cpp
#include "CPlusPlusPlus/All.h"

// 设置随机种子
Random::set_seed(42);

// 生成随机数
int r1 = Random::rand_int(1, 100);        // 1-100 的整数
double r2 = Random::rand_double();         // 0-1 的浮点数
bool r3 = Random::rand_bool();             // true/false

// 打乱容器
std::vector<int> vec = {1, 2, 3, 4, 5};
Random::shuffle(vec);

// 随机选择
auto choice = Random::rand_choice(vec);
if (choice) {
    std::cout << "选中: " << *choice << std::endl;
}
```

## 高级数据结构

### AVL 树

```cpp
DataStructures::avl_tree<int> tree;
tree.insert(50);
tree.insert(30);
tree.insert(70);

if (tree.contains(30)) {
    std::cout << "找到 30" << std::endl;
}

std::cout << "树高度: " << tree.height() << std::endl;
```

### 图

```cpp
DataStructures::graph<int> g;
g.add_undirected_edge(1, 2);
g.add_undirected_edge(2, 3);
g.add_undirected_edge(3, 4);

// 广度优先搜索
auto result = g.bfs(1);
for (int node : result) {
    std::cout << node << " ";
}
```

### 并查集

```cpp
DataStructures::disjoint_set<int> ds;
ds.make_set(1);
ds.make_set(2);
ds.make_set(3);

ds.union_sets(1, 2);

if (ds.is_connected(1, 2)) {
    std::cout << "1 和 2 连通" << std::endl;
}
```

## 最佳实践

1. **包含头文件**: 始终包含 `CPlusPlusPlus/All.h` 以使用所有特性
2. **特性选择**: 根据需要启用/禁用特性，减少编译时间
3. **错误处理**: 使用 `auto?` 和 `?` 运算符进行优雅的错误处理
4. **资源管理**: 使用 `defer` 确保资源正确释放
5. **兼容性**: 确保代码在不使用插件时也能编译为有效 C++

## 编译选项

```bash
# 优化编译
clang++ -O2 -Xclang -load -Xclang ClangCPlusPlusPlus.dll -I include -std=c++17 your_file.cpp

# 调试编译
clang++ -g -Xclang -load -Xclang ClangCPlusPlusPlus.dll -I include -std=c++17 your_file.cpp

# 启用所有警告
clang++ -Wall -Wextra -Xclang -load -Xclang ClangCPlusPlusPlus.dll -I include -std=c++17 your_file.cpp
```
