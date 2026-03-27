# C+++ 设计文档

## 1. 项目架构

C+++ 项目采用模块化设计，主要由以下几个部分组成：

### 1.1 核心组件

1. **词法分析器（Lexer）**：负责识别C+++的新关键字和运算符
2. **语法分析器（Parser）**：负责解析C+++的新语法结构
3. **AST转换器（Transformer）**：负责将C+++的AST转换为标准C++的AST
4. **标准库增强**：提供Better Random库和高级数据结构

### 1.2 目录结构

```
CPlusPlusPlus-release/
├── docs/                # 文档
│   ├── USAGE.md         # 使用说明
│   └── DESIGN.md        # 设计文档
├── examples/            # 示例代码
├── include/             # 头文件
│   └── CPlusPlusPlus/   # 核心头文件
├── lib/                 # 实现文件
│   └── CPlusPlusPlus/   # 核心实现
├── tests/               # 测试代码
├── CMakeLists.txt       # 主CMake配置
└── README.md            # 项目说明
```

## 2. 实现细节

### 2.1 词法分析器

词法分析器负责识别C+++的新关键字和运算符，主要实现包括：

- 定义C+++关键字列表：`let`、`var`、`defer`、`match`、`interface`
- 实现`registerKeywords`函数，用于在Clang插件初始化时注册这些关键字
- 实现`getOperatorKind`函数，用于处理新的运算符，如管道运算符`|>`和错误传播运算符`??`

### 2.2 语法分析器

语法分析器负责解析C+++的新语法结构，主要实现包括：

- 解析`let`/`var`变量声明
- 解析`auto?`可选类型
- 解析`defer`语句
- 解析错误传播运算符`?`
- 解析管道运算符`|>`
- 解析`if let`/`while let`模式匹配
- 解析默认参数占位符`_`
- 解析`@property`注解
- 解析`interface`关键字
- 解析容器字面量扩展
- 解析多容器并行for循环

### 2.3 AST转换器

AST转换器负责将C+++的AST转换为标准C++的AST，主要实现包括：

- 将`let`变量转换为`const auto`变量
- 将`var`变量转换为`auto`变量
- 将`defer`语句转换为RAII guard类
- 将错误传播运算符`?`转换为条件表达式
- 将管道运算符`|>`转换为函数调用
- 将`interface`转换为纯虚基类
- 将`@property`转换为getter/setter方法
- 将多容器并行for循环转换为标准for循环

### 2.4 标准库增强

#### 2.4.1 Better Random库

Better Random库提供了易用的随机数生成功能，主要实现包括：

- `rand_int`：生成指定范围内的随机整数
- `rand_double`：生成指定范围内的随机浮点数
- `rand_bool`：生成随机布尔值
- `rand_choice`：从容器中随机选择一个元素
- `shuffle`：打乱容器元素
- `rand_sample`：从容器中随机采样n个元素
- `set_seed`：设置随机种子
- `rand_normal`：生成正态分布的随机数

#### 2.4.2 高级数据结构

高级数据结构提供了多种常用的数据结构，主要实现包括：

- `avl_tree`：平衡二叉搜索树
- `skip_list`：跳表
- `splay_tree`：伸展树
- `disjoint_set`：并查集
- `graph`：图，支持BFS、DFS和Dijkstra算法

#### 2.4.3 容器增强

容器增强提供了对标准容器的扩展，主要实现包括：

- `zip`函数：用于并行迭代多个容器

#### 2.4.4 控制流增强

控制流增强提供了对控制流的扩展，主要实现包括：

- `DeferGuard`类：用于实现defer语句的功能
- 错误传播辅助类：用于实现错误传播运算符的功能
- 管道运算符辅助类：用于实现管道运算符的功能

#### 2.4.5 面向对象增强

面向对象增强提供了对面向对象编程的扩展，主要实现包括：

- `PropertyAttribute`类：用于实现@property的功能
- `InterfaceBase`类：用于实现interface的功能
- `CPLUSPLUSPLUS_PROPERTY`宏：用于手动创建属性
- `CPLUSPLUSPLUS_PROPERTY_READONLY`宏：用于手动创建只读属性
- `CPLUSPLUSPLUS_INTERFACE`宏：用于手动创建接口

## 3. 工作原理

C+++ 项目基于Clang插件框架实现，其工作原理如下：

1. **插件初始化**：当Clang加载C+++插件时，插件会注册C+++的新关键字和运算符。
2. **词法分析**：词法分析器会识别C+++的新关键字和运算符，并将它们转换为对应的token。
3. **语法分析**：语法分析器会解析C+++的新语法结构，并构建对应的AST节点。
4. **AST转换**：AST转换器会遍历AST，将C+++的AST节点转换为标准C++的AST节点。
5. **代码生成**：Clang会使用转换后的AST生成标准C++代码。

## 4. 特性实现方式

### 4.1 let/var

- **实现方式**：通过AST转换器将`let`转换为`const auto`，将`var`转换为`auto`。
- **示例**：
  ```cpp
  let x = 42;  // 转换为 const auto x = 42;
  var y = 3.14; // 转换为 auto y = 3.14;
  ```

### 4.2 defer

- **实现方式**：通过AST转换器将`defer`语句转换为RAII guard类。
- **示例**：
  ```cpp
  defer {
      fclose(file);
  }; // 转换为 DeferGuard guard([]() { fclose(file); });
  ```

### 4.3 错误传播运算符?

- **实现方式**：通过AST转换器将`?`运算符转换为条件表达式。
- **示例**：
  ```cpp
  auto result = divide(10, 2) ? divide(*result, 2); // 转换为条件表达式
  ```

### 4.4 管道运算符|>

- **实现方式**：通过AST转换器将`|>`运算符转换为函数调用。
- **示例**：
  ```cpp
  auto result = 5 |> square |> add_one; // 转换为 add_one(square(5))
  ```

### 4.5 match

- **实现方式**：通过AST转换器将`match`语句转换为switch语句或if-else语句。
- **示例**：
  ```cpp
  match (value) {
      case 0: /* 处理零 */ break;
      case 1 ... 10: /* 处理1-10 */ break;
      default: /* 处理其他情况 */ break;
  } // 转换为switch语句或if-else语句
  ```

### 4.6 @property

- **实现方式**：通过AST转换器将`@property`转换为getter/setter方法。
- **示例**：
  ```cpp
  @property(std::string) name; // 转换为私有成员变量和getter/setter方法
  ```

### 4.7 interface

- **实现方式**：通过AST转换器将`interface`转换为纯虚基类。
- **示例**：
  ```cpp
  interface Drawable {
      void draw() const;
  }; // 转换为纯虚基类
  ```

### 4.8 并行for循环

- **实现方式**：通过AST转换器将多容器并行for循环转换为标准for循环，使用`zip`函数进行并行迭代。
- **示例**：
  ```cpp
  for (auto [i, x, y] : zip(a, b)) {
      result[i] = x + y;
  } // 转换为使用zip函数的标准for循环
  ```

## 5. 性能考虑

### 5.1 编译时间

- **特性选择**：用户可以通过宏定义选择性启用/禁用特性，减少编译时间。
- **AST转换**：AST转换只在编译时进行，不会影响运行时性能。

### 5.2 运行时性能

- **语法糖**：语法糖转换为标准C++代码后，运行时性能与手写的标准C++代码相同。
- **标准库增强**：标准库增强功能经过优化，性能与标准库相当或更好。

## 6. 兼容性

### 6.1 ISO C++兼容性

- **向后兼容**：当不使用插件时，所有C+++代码都是有效的ISO C++代码。
- **标准合规**：转换后的代码符合ISO C++标准。

### 6.2 平台兼容性

- **跨平台**：支持Windows、Linux和macOS平台。
- **Clang版本**：需要Clang 11.0.0或更新版本。

## 7. 未来计划

### 7.1 功能扩展

- **更多语法糖**：计划添加更多现代语言特性，如协程、模式匹配增强等。
- **更多标准库增强**：计划添加更多高级数据结构和算法。

### 7.2 性能优化

- **编译时间优化**：优化AST转换过程，减少编译时间。
- **运行时优化**：优化标准库增强功能的性能。

### 7.3 工具支持

- **IDE集成**：计划添加IDE插件，提供更好的开发体验。
- **静态分析**：计划添加静态分析工具，帮助用户发现潜在问题。

## 8. 结论

C+++ 项目通过添加现代化的语法糖和增强的标准库功能，为C++开发者提供了更现代、更易用的编程体验，同时保持与ISO C++的完全兼容性。项目的模块化设计和清晰的架构为后续的功能扩展和性能优化奠定了良好的基础。