# C+++ 安装指南

## 系统要求

- **操作系统**: Windows 10/11, Linux, macOS
- **编译器**: Clang 11.0.0 或更新版本
- **构建工具**: CMake 3.10+
- **C++标准**: C++17 或更新版本

## 从源码编译

### 1. 克隆仓库

```bash
git clone https://github.com/YOUR_USERNAME/cplusplusplus.git
cd cplusplusplus
```

### 2. 安装依赖

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install -y clang llvm-dev cmake
```

#### macOS
```bash
brew install llvm cmake
```

#### Windows
- 安装 [LLVM](https://releases.llvm.org/download.html)
- 安装 [CMake](https://cmake.org/download/)
- 安装 Visual Studio 2019 或更新版本

### 3. 编译插件

```bash
# 创建构建目录
mkdir build
cd build

# 配置
cmake ..

# 编译
cmake --build . --config Release

# 安装（可选）
cmake --install . --prefix /usr/local
```

### 4. 验证编译

```bash
# Linux/macOS
ls -la lib/ClangCPlusPlusPlus.*

# Windows
ls -la bin/ClangCPlusPlusPlus.dll
```

## 使用预编译版本

如果不想自己编译，可以下载预编译版本：

### Windows

1. **下载** `CPlusPlusPlus-windows-x64.zip`
2. **解压** 到任意目录，例如 `C:\CPlusPlusPlus`
3. **设置环境变量**（可选）
   ```
   将 C:\CPlusPlusPlus\bin 添加到系统 PATH
   ```

### Linux

1. **下载** `CPlusPlusPlus-linux-x64.tar.gz`
2. **解压**
   ```bash
   tar -xzf CPlusPlusPlus-linux-x64.tar.gz -C /usr/local/
   ```
3. **设置环境变量**
   ```bash
   export PATH=$PATH:/usr/local/CPlusPlusPlus/bin
   ```

### macOS

1. **下载** `CPlusPlusPlus-macos-x64.tar.gz`
2. **解压**
   ```bash
   tar -xzf CPlusPlusPlus-macos-x64.tar.gz -C /usr/local/
   ```
3. **设置环境变量**
   ```bash
   export PATH=$PATH:/usr/local/CPlusPlusPlus/bin
   ```

## 编译示例程序

### 基本编译命令

```bash
# Windows
clang++ -Xclang -load -Xclang C:\CPlusPlusPlus\bin\ClangCPlusPlusPlus.dll -I C:\CPlusPlusPlus\include -std=c++17 your_file.cpp -o your_program.exe

# Linux
clang++ -Xclang -load -Xclang /usr/local/CPlusPlusPlus/lib/libClangCPlusPlusPlus.so -I /usr/local/CPlusPlusPlus/include -std=c++17 your_file.cpp -o your_program

# macOS
clang++ -Xclang -load -Xclang /usr/local/CPlusPlusPlus/lib/libClangCPlusPlusPlus.dylib -I /usr/local/CPlusPlusPlus/include -std=c++17 your_file.cpp -o your_program
```

### 运行示例

```bash
cd examples

# 编译
clang++ -Xclang -load -Xclang ../build/bin/ClangCPlusPlusPlus.dll -I ../include -std=c++17 basic_syntax.cpp -o basic_syntax.exe

# 运行
./basic_syntax.exe
```

## 目录结构

```
cplusplusplus/
├── CMakeLists.txt              # 主CMake配置
├── README.md                   # 项目说明
├── INSTALL.md                  # 本文件
├── LICENSE                     # 许可证
├── docs/
│   └── USAGE.md                # 使用手册
├── include/
│   └── CPlusPlusPlus/          # 头文件
├── lib/
│   └── CPlusPlusPlus/          # 源代码
│       ├── CMakeLists.txt
│       ├── CPlusPlusPlus.cpp
│       ├── Lexer.cpp
│       ├── Parser.cpp
│       └── Transformer.cpp
└── examples/                   # 示例代码
```

## 故障排除

### 问题1: 找不到 LLVM/Clang

**错误信息**: `Could not find a package configuration file provided by "LLVM"`

**解决方案**:
```bash
# 指定 LLVM 路径
cmake -DLLVM_DIR=/usr/lib/llvm-14/lib/cmake/llvm ..

# 或
cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/llvm ..
```

### 问题2: 找不到插件

**错误信息**: `unable to load plugin`

**解决方案**:
- 检查插件路径是否正确
- 确保使用与插件相同版本的 Clang
- Windows: 确保 Visual C++ Redistributable 已安装

### 问题3: MSVC STL 版本不兼容

**错误信息**: `Unexpected compiler version`

**解决方案**:
- 使用 MinGW 版本的 Clang
- 或者使用 libc++ 替代 MSVC STL
- 或者升级 Clang 到 19.0.0 或更新版本

## 下一步

- 阅读 [README.md](README.md) 了解 C+++ 特性
- 查看 [docs/USAGE.md](docs/USAGE.md) 了解详细用法
- 运行 [examples/](examples/) 目录中的示例代码

## 获取帮助

- 项目主页: https://github.com/YOUR_USERNAME/cplusplusplus
- 问题反馈: https://github.com/YOUR_USERNAME/cplusplusplus/issues
