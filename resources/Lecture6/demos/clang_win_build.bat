@echo off
setlocal enabledelayedexpansion

where clang >nul 2>nul
if %ERRORLEVEL% neq 0 goto SkipBuild

set argCount=0
for %%x in (%*) do (
   set /A argCount+=1
   set "argVec[!argCount!]=%%~x"
)

if %argCount% equ 0 (
   echo Usage: clang_win_build [files]
   goto :Finished
)

if not exist "clang_debug" mkdir clang_debug
for /L %%i in (1,1,%argCount%) do (
    echo Building Debug !argVec[%%i]!
    clang  .\!argVec[%%i]! -D _CRT_SECURE_NO_WARNINGS -o .\clang_debug\!argVec[%%i]:~0,-2!.exe
)

echo ------------------------------------

if not exist "clang_optimized" mkdir clang_optimized
for /L %%i in (1,1,%argCount%) do (
    echo Building Optimized !argVec[%%i]!
    clang  .\!argVec[%%i]! -D _CRT_SECURE_NO_WARNINGS -o .\clang_optimized\!argVec[%%i]:~0,-2!.exe -O2
)

goto Finished

:SkipBuild
echo "Compiler not present! Run using developer prompt"

:Finished