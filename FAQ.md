# FAQ

## 常见问题解答

### 为什么要编译 Clang 插件？

C+++ 是通过 Clang 插件实现的，因为它需要对 C++ 代码进行语法扩展和转换。编译插件是为了获得这些增强的语法特性和标准库功能。插件会在编译过程中对 C+++ 代码进行处理，将其转换为标准 C++ 代码，然后再由编译器编译。

### C+++ 和 CppFront 的区别是什么？

- **实现方式**：C+++ 是通过 Clang 插件实现的，而 CppFront 是一个独立的编译器前端。

- **兼容性**：C+++ 保持与 ISO C++ 的完全兼容性，当不使用插件时，所有 C+++ 代码都是有效的 ISO C++ 代码。

- **语法扩展**：C+++ 提供了更丰富的语法糖和标准库增强，如 `defer` 语句、管道运算符、模式匹配等。

- **集成度**：C+++ 作为 Clang 的插件，与 Clang 编译器紧密集成，而 CppFront 是一个独立工具。

### C+++ 兼容哪些版本的 Clang 和 C++ 标准？

- **Clang 版本**：需要 Clang 11.0.0 或更新版本。

- **C++ 标准**：支持 C++17 及以上版本。

- **平台**：兼容 Windows、Linux 和 macOS。

### 如何启用或禁用特定特性？

你可以使用预处理指令来启用或禁用特定特性：

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

### C+++ 如何保持与 ISO C++ 的兼容性？

C+++ 的设计理念是保持与 ISO C++ 的完全兼容性。当不使用插件时，所有 C+++ 代码都是有效的 ISO C++ 代码。这意味着你可以逐步采用 C+++ 的特性，而不需要完全重写现有代码。

### 如何获取 C+++ 的最新版本？

C+++ 基于 LLVM/Clang 开发，通过克隆官方仓库并编译即可获取最新版本，完整流程如下：

```bash
# 1. 克隆 LLVM 官方仓库（包含 Clang 核心）
git clone https://github.com/llvm/llvm-project.git
cd llvm-project

# 2. 克隆 C+++ 插件源码到 Clang 工具目录
git clone https://github.com/TBNLZLDYD/cplusplusplus.git clang-tools-extra/ClangCPlusPlusPlus

# 3. 创建构建目录并编译
mkdir build && cd build
cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release ../llvm
cmake --build . --config Release --target ClangCPlusPlusPlus
```

编译完成后，会自动生成可直接使用的 Clang C+++ 插件。

### C+++ 的性能影响如何？

C+++ 的语法扩展在编译时被转换为标准 C++ 代码，因此运行时性能与标准 C++ 代码相同。编译时间可能会略有增加，因为插件需要对代码进行额外处理，但这种影响通常很小。

### 如何贡献到 C+++ 项目？

你可以通过以下步骤为 C+++ 贡献代码：

1. 克隆 LLVM/Clang/C+++ 仓库

2. 创建一个新分支

3. 实现你的更改

4. 运行测试

5. 提交拉取请求

### C+++ 是否支持其他编译器？

目前，C+++ 只支持 Clang 编译器，因为它是通过 Clang 插件实现的。未来可能会考虑支持其他编译器，但这需要不同的实现方式。

### 如何报告 C+++ 的 bug？

你可以在 C+++ 项目的 Issue 跟踪器中提交 bug 反馈：

[https://github.com/TBNLZLDYD/cplusplusplus/issues](https://github.com/TBNLZLDYD/cplusplusplus/issues)

请在报告中包含以下信息：

- C+++ 版本

- Clang 版本

- 操作系统

- 重现步骤

- 预期行为

- 实际行为
