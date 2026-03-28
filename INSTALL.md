# C+++ 安装指南

## 系统要求

- **操作系统**: Windows 10/11 (64位), Linux (x86_64), macOS (10.15及以上)

- **编译器**: Clang 11.0.0 或更新版本（推荐Clang 19.0.0+，解决MSVC STL兼容问题）

- **构建工具**: CMake 3.10+（推荐CMake 3.20+，提升兼容性）

- **C++标准**: C++17 或更新版本（支持C++20，可按需指定）

## 从源码编译

### 1. 克隆仓库

```bash
git clone https://github.com/TBNLZLDYD/cplusplusplus.git
cd cplusplusplus
```

### 2. 安装依赖

#### Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install -y clang llvm-dev cmake llvm-config
```

#### macOS

```bash
brew install llvm cmake
brew link llvm --force
```

#### Windows

- 安装 [LLVM](https://releases.llvm.org/download.html)（选择Windows x64版本，安装时勾选“Add LLVM to PATH”）

- 安装 [CMake](https://cmake.org/download/)（勾选“Add CMake to system PATH”）

- 安装 Visual Studio 2019 或更新版本（需勾选“使用C++的桌面开发”组件，提供MSVC编译环境）

### 3. 编译插件

```bash
# 创建构建目录
mkdir build
cd build
# 配置（指定Clang编译器，避免使用系统默认GCC）
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
# 编译
cmake --build . --config Release
# 安装（可选，Linux/macOS推荐，Windows可跳过）
cmake --install . --prefix /usr/local
```

### 4. 验证编译

```bash
# Linux/macOS（在build目录下执行）
ls -la lib/ClangCPlusPlusPlus.*
# Windows（在build目录下执行，PowerShell或CMD）
dir bin\ClangCPlusPlusPlus.dll
```

## 使用预编译版本

如果不想自己编译，可以下载预编译版本（下载地址可在项目主页获取）：

### Windows

1. **下载** `CPlusPlusPlus-windows-x64.zip`（需对应系统位数，仅支持64位）

2. **解压** 到任意目录，例如 `C:\CPlusPlusPlus`（建议路径无中文、无空格）

3. **设置环境变量**（可选，方便全局调用）`将 C:\CPlusPlusPlus\bin 添加到系统 PATH 环境变量，重启终端生效`

### Linux

1. **下载** `CPlusPlusPlus-linux-x64.tar.gz`

2. **解压**`tar -xzf CPlusPlusPlus-linux-x64.tar.gz -C /usr/local/`

3. **设置环境变量**（永久生效）
        `echo "export PATH=$PATH:/usr/local/CPlusPlusPlus/bin" >> ~/.bashrc
source ~/.bashrc`

### macOS

1. **下载** `CPlusPlusPlus-macos-x64.tar.gz`

2. **解压**`tar -xzf CPlusPlusPlus-macos-x64.tar.gz -C /usr/local/`

3. **设置环境变量**（永久生效）
        `echo "export PATH=$PATH:/usr/local/CPlusPlusPlus/bin" >> ~/.zshrc
source ~/.zshrc`说明：若使用bash，替换为~/.bashrc；若使用fish，替换为~/.config/fish/config.fish。

## 编译示例程序

### 基本编译命令

```bash
# Windows（预编译版本）
clang++ -Xclang -load -Xclang C:\CPlusPlusPlus\bin\ClangCPlusPlusPlus.dll -I C:\CPlusPlusPlus\include -std=c++17 your_file.cpp -o your_program.exe
# Windows（源码编译版本，build目录下）
clang++ -Xclang -load -Xclang build\bin\ClangCPlusPlusPlus.dll -I include -std=c++17 your_file.cpp -o your_program.exe
# Linux（预编译/源码编译通用）
clang++ -Xclang -load -Xclang /usr/local/CPlusPlusPlus/lib/libClangCPlusPlusPlus.so -I /usr/local/CPlusPlusPlus/include -std=c++17 your_file.cpp -o your_program
# macOS（预编译/源码编译通用）
clang++ -Xclang -load -Xclang /usr/local/CPlusPlusPlus/lib/libClangCPlusPlusPlus.dylib -I /usr/local/CPlusPlusPlus/include -std=c++17 your_file.cpp -o your_program
```

### 运行示例

```bash
cd examples
# 编译（Windows，源码编译版本）
clang++ -Xclang -load -Xclang ../build/bin/ClangCPlusPlusPlus.dll -I ../include -std=c++17 basic_syntax.cpp -o basic_syntax.exe
# 编译（Linux/macOS，源码编译版本）
clang++ -Xclang -load -Xclang ../build/lib/libClangCPlusPlusPlus.so -I ../include -std=c++17 basic_syntax.cpp -o basic_syntax
# 运行（Windows）
.\basic_syntax.exe
# 运行（Linux/macOS）
./basic_syntax
```

## 目录结构

```bash
cplusplusplus/
├── CMakeLists.txt              # 主CMake配置
├── README.md                   # 项目说明
├── INSTALL.md                  # 本文件
├── LICENSE                     # 许可证
├── docs/
│   └── USAGE.md                # 使用手册
├── include/
│   └── CPlusPlusPlus/          # 头文件
├── src/                        # 源代码（修正：原lib目录用于存放编译产物，源码移至src目录，符合常规规范）
│   └── CPlusPlusPlus/
│       ├── CMakeLists.txt
│       ├── CPlusPlusPlus.cpp
│       ├── Lexer.cpp
│       ├── Parser.cpp
│       └── Transformer.cpp
├── lib/                        # 编译产物（库文件）
└── examples/                   # 示例代码
```

## 故障排除

### 问题1: 找不到 LLVM/Clang

**错误信息**: `Could not find a package configuration file provided by "LLVM"`

**解决方案**:

```bash
# Linux（指定LLVM路径，需根据实际安装路径调整）
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_DIR=/usr/lib/llvm-14/lib/cmake/llvm ..
# macOS（brew安装的LLVM路径）
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_PREFIX_PATH=/usr/local/opt/llvm ..
# Windows（LLVM默认安装路径）
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_DIR="C:\Program Files\LLVM\lib\cmake\llvm" ..
```

### 问题2: 找不到插件

**错误信息**: `unable to load plugin`

**解决方案**:

- 检查插件路径是否正确（区分系统后缀：.dll/.so/.dylib）

- 确保使用与插件编译时相同版本的Clang（版本不匹配会导致加载失败）

- Windows: 安装 Visual C++ Redistributable 2019 或以上版本（需对应系统位数，64位优先）

### 问题3: MSVC STL 版本不兼容

**错误信息**: `Unexpected compiler version`

**解决方案**:

- 使用 MinGW 版本的 Clang（避免MSVC STL适配问题）

- 或者使用 libc++ 替代 MSVC STL（添加编译参数：-stdlib=libc++）

- 或者升级 Clang 到 19.0.0 或更新版本（彻底解决MSVC STL兼容问题）

## 下一步

- 阅读 [README.md](https://www.doubao.cn) 了解 C+++ 特性

- 查看 [docs/USAGE.md](https://www.doubao.cn) 了解详细用法

- 运行 [examples/](https://www.doubao.cn) 目录中的示例代码，验证安装是否成功

## 获取帮助

- 项目主页: https://github.com/TBNLZLDYD/cplusplusplus

- 问题反馈: https://github.com/TBNLZLDYD/cplusplusplus/issues
> （注：文档部分内容可能由 AI 生成）
