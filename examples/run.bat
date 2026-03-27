@echo off

set PLUGIN_PATH=..\bin\ClangCPlusPlusPlus.dll
set INCLUDE_PATH=..\include

for %%f in (*.cpp) do (
    echo Compiling %%f...
    clang++ -Xclang -load -Xclang %PLUGIN_PATH% -I %INCLUDE_PATH% -std=c++17 %%f -o %%~nf.exe
    if errorlevel 1 (
        echo Compilation failed for %%f
    ) else (
        echo Running %%~nf.exe...
        %%~nf.exe
        echo ------------------------
    )
)

echo All examples completed!
pause