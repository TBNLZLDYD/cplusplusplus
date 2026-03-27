#!/bin/bash

PLUGIN_PATH="../bin/libClangCPlusPlusPlus.so"
INCLUDE_PATH="../include"

for file in *.cpp; do
    echo "Compiling $file..."
    clang++ -Xclang -load -Xclang "$PLUGIN_PATH" -I "$INCLUDE_PATH" -std=c++17 "$file" -o "${file%.cpp}"
    if [ $? -ne 0 ]; then
        echo "Compilation failed for $file"
    else
        echo "Running ${file%.cpp}..."
        "./${file%.cpp}"
        echo "------------------------"
    fi
done

echo "All examples completed!"