#include <stdio.h>
// constants
#define PI 3.14

// macros
#define add(a, b) a + b
#define square(r) r *r

// multiline macros
#define MACRO(num, str)                                         \
        printf("%d", num);         \
        printf(" is");             \
        printf(" %s number", str); \
        printf("\n");              \
    

int main(int argc, char const *argv[])
{
    MACRO(1, "one");
    return 0;
}
