# 示例程序的CMake配置

# 包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# 示例程序列表
set(EXAMPLES
    basic_syntax
    error_propagation
    interface
    parallel_for
    pattern_matching
    pipe_operator
    property
    random
)

# 为每个示例创建可执行文件
foreach(EXAMPLE ${EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    target_link_libraries(${EXAMPLE} CPlusPlusPlus)
endforeach()