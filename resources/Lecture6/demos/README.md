## Multithreading-I
### The sample codes for Lecture-5 of Advanced C Workshop
Three scripts are provided to compile the programs.
Currently supported compilers are MSVC and Clang for Windows and gcc and Clang for Linux.
To compile all supported files in linux, run
```
linux_build *.c
``` 

Files with **Lmt** prefix are Linux specific and won't compile on Windows.

To build using MSVC, run `cl_build.bat` from **Developer Command Prompt for VS**. The script takes in the files to compile; to compile all the files run
```
cl_build mt*.c
```

To build all the files using Clang in windows, run
```
clang_win_build mt*.c
```