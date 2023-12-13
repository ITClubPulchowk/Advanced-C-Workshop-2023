#include<stdio.h>
#include<stdalign.h>  
  
// struct is aligned to 16 bytes in memory. 
struct alignas(16) Demo 
{ 
  
    int var1l; // 4 bytes 
    int var2; // 4 bytes 
    short s; // 2 bytes 
    // char aligned to 4 bytes in memory. 
    alignas(4) char arr[5]; 
}; 
  
// driver code 
int main() 
{ 
    printf(alignof(Demo)) // output: 16 
    return 0; 
}





