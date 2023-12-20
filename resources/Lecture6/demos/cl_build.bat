@echo off
setlocal enabledelayedexpansion

where cl >NUL 2>NUL
if %ERRORLEVEL% neq 0 goto :SkipBuild

set argCount=0
for %%x in (%*) do (
   set /A argCount+=1
   set "argVec[!argCount!]=%%~x"
)

if %argCount% equ 0 (
   echo Usage: cl_build [files]
   goto :Finished
)

if not exist "cl_debug" mkdir cl_debug
echo Debug Builds
pushd cl_debug
for /L %%i in (1,1,%argCount%) do cl /nologo /Zi /D_CRT_SECURE_NO_WARNINGS=1 ../!argVec[%%i]! 
popd

if not exist "cl_optimized" mkdir cl_optimized
echo -----------------------------------
echo Optimized Builds
pushd cl_optimized
for /L %%i in (1,1,%argCount%) do cl /nologo /Zi /O2 /D_CRT_SECURE_NO_WARNINGS=1 ../!argVec[%%i]! 
popd

goto Finished

:SkipBuild
echo "Compiler not present! Run using developer prompt"

:Finished