#!/bin/bash

which gcc &> /dev/null
if [ $? == 0 ]
then
    COMPILER=gcc
else
    echo gcc not found
fi
echo Building with $COMPILER

# echo Building runner
# ${COMPILER} ./runner.c -o runner -O2

####################################################################################################

mkdir -p gcc_debug

for arg in $@; do
    echo Building Debug $arg
    ${COMPILER} $arg -o ./gcc_debug/${arg%.*} -lpthread
done

#############################################################################################

echo -----------------------------------------------
mkdir -p gcc_optimized

for arg in $@; do
    echo Building Optimized $arg
    ${COMPILER} $arg -o ./gcc_optimized/${arg%.*} -O1 -lpthread
done

echo ===============================================

which clang &> /dev/null
if [ $? == 0 ]
then
    COMPILER=clang
else
    echo No compiler found
    exit
fi

echo Building with $COMPILER

mkdir -p clang_linux_debug

for arg in $@; do
    echo Building Debug $arg
    ${COMPILER} $arg -o ./clang_linux_debug/${arg%.*} -lpthread
done

#############################################################################################

echo -----------------------------------------------
mkdir -p clang_linux_optimized

for arg in $@; do
    echo Building Optimized $arg
    ${COMPILER} $arg -o ./clang_linux_optimized/${arg%.*} -O1 -lpthread
done

