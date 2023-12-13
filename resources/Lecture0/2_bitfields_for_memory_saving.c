#include<stdio.h>

int main()
{
    struct time {
        unsigned int hours   : 5; // 0 to 23 can be represented by log2(24) = 5 bits
        unsigned int minutes : 6; // 0 to 59 can be represented by log2(59) = 6 bits
        unsigned int seconds : 6; // 0 to 59 can be represented by log2(59) = 6 bits
    };
    struct time t = {10,30,45};
    printf("Display time as:\n");
    printf("%d : %d : %d\n", t.hours, t.minutes, t.seconds);
    printf("The size of time struct 't' is: %d\n", sizeof(t));
    return 0;
}