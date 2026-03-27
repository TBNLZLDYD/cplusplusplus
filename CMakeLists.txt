cmake_minimum_required(VERSION 3.10)
project(CPlusPlusPlus VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 LLVM 和 Clang
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Using ClangConfig.cmake in: ${Clang_DIR}")

# 包含目录
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_definitions(${LLVM_DEFINITIONS})

# 创建共享库（插件）
add_library(ClangCPlusPlusPlus SHARED
    lib/CPlusPlusPlus/CPlusPlusPlus.cpp
    lib/CPlusPlusPlus/Lexer.cpp
    lib/CPlusPlusPlus/Parser.cpp
    lib/CPlusPlusPlus/Transformer.cpp
)

# 链接 Clang 和 LLVM 库
target_link_libraries(ClangCPlusPlusPlus
    clangAST
    clangBasic
    clangFrontend
    clangLex
    clangParse
    clangSema
    LLVMCore
    LLVMSupport
)

# 设置输出目录
set_target_properties(ClangCPlusPlusPlus PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 安装规则
install(TARGETS ClangCPlusPlusPlus
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/CPlusPlusPlus
    DESTINATION include
)

install(FILES README.md INSTALL.md LICENSE
    DESTINATION share/CPlusPlusPlus
)

# 示例程序（可选）
option(BUILD_EXAMPLES "Build example programs" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()