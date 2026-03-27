cmake_minimum_required(VERSION 3.10)
project(CPlusPlusPlus VERSION 0.1.0 LANGUAGES CXX)

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
add_library(CPlusPlusPlus SHARED
    lib/CPlusPlusPlus/CPlusPlusPlus.cpp
    lib/CPlusPlusPlus/Lexer.cpp
    lib/CPlusPlusPlus/Parser.cpp
    lib/CPlusPlusPlus/Transformer.cpp
    lib/CPlusPlusPlus/Features.cpp
)

# 链接 Clang 和 LLVM 库
target_link_libraries(CPlusPlusPlus
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
set_target_properties(CPlusPlusPlus PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 安装规则
install(TARGETS CPlusPlusPlus
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

# 测试程序
option(BUILD_TESTS "Build test programs" ON)
if(BUILD_TESTS)
    add_executable(test_random tests/test_random.cpp)
    target_link_libraries(test_random CPlusPlusPlus)
    
    add_executable(test_datastructures tests/test_datastructures.cpp)
    target_link_libraries(test_datastructures CPlusPlusPlus)
    
    add_executable(test_container tests/test_container.cpp)
    target_link_libraries(test_container CPlusPlusPlus)
    
    add_executable(test_controlflow tests/test_controlflow.cpp)
    target_link_libraries(test_controlflow CPlusPlusPlus)
    
    add_executable(test_oop tests/test_oop.cpp)
    target_link_libraries(test_oop CPlusPlusPlus)
endif()