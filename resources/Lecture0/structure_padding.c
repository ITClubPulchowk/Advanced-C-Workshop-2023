// #pragma pack(1)
#include<stdio.h>

/*
-------------------------
|char        |  1 byte  |
|short int   |  2 bytes |
|int         |  4 bytes |
|long int    |  8 bytes |
|double      |  8 bytes |
|pointer     |  8 bytes |
-------------------------
*/

struct abc {
    char a;             // 1 byte
    int b;              // 4 bytes
    // int* pointer;       // 8 bytes 
    char c;             // 1 byte
    // char d;
};

int main() {
    struct abc structure_variable;
    
    printf("The of struct variable is: %d bytes", sizeof(structure_variable)); 
    printf("\n");
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    char character_variable;
    printf("The size of normal char variable is: %d bytes", sizeof(character_variable));
    printf("\n");
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    double long_integer;
    printf("The size of normal long int variable is: %d bytes", sizeof(long_integer));
    printf("\n");
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    float floating_point;
    printf("The size of normal float variable is: %d bytes", sizeof(floating_point));
    printf("\n");
    return 0;
}